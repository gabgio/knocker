/* knocker version 0.8.0
 * Release date: 28 December 2020
 *
 * Project homepage: https://knocker.sourceforge.io
 *
 * Copyright 2001,2020 Gabriele Giorgetti <g.giorgetti@gmail.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <errno.h>

#include "knocker_core.h"
#include "knocker_services.h"


static int knocker_core_init_port_data (knocker_core_port_t * port);
static void knocker_core_free_port_data (knocker_core_port_t * port);

static int knocker_core_init_socket_data (knocker_core_socket_t * sock);
static void knocker_core_free_socket_data (knocker_core_socket_t * sock);
static int knocker_core_open_socket (knocker_core_socket_t * sock, int protocol);
static void knocker_core_close_socket (knocker_core_socket_t * sock);

static int knocker_core_init_host_data (knocker_core_host_t * host);
static void knocker_core_free_host_data (knocker_core_host_t * host);

static int knocker_core_gethostbyname (knocker_core_host_t * hinfo, const char *hostname);
static int knocker_core_getservbyport (char *service, unsigned int port, int protocol);

static char *knocker_core_get_host_name_string (knocker_core_host_t * hinfo);
static char *knocker_core_get_host_ip_string (knocker_core_host_t * hinfo);
static int knocker_core_set_host_name_string (knocker_core_host_t * hinfo, const char *hostname);
static int knocker_core_set_host_ip_string (knocker_core_host_t * hinfo, const char *hostip);
static void knocker_core_free_host_name_string (knocker_core_host_t * hinfo);
static void knocker_core_free_host_ip_string (knocker_core_host_t * hinfo);

static inline int _connect_nonblocking(int sock, struct sockaddr_in sa, int timeout);

/* allocated and deallocated within knocker_core_init, knocker_core_quit */
char *knocker_core_last_hostip;   /* string of the last resolved host ip address */
char *knocker_core_last_hostname; /* string of the last used host name */
char *knocker_core_last_service;  /* string of the last service */


inline int _connect_nonblocking(int sock, struct sockaddr_in sa, int timeout)
{
    int flags = 0, error = 0, ret = 0;
    fd_set  rset, wset;
    socklen_t   len = sizeof(error);
    struct timeval  ts;

    ts.tv_sec = timeout;
    ts.tv_usec = 0;

    //clear out descriptor sets for select
    //add socket to the descriptor sets
    FD_ZERO(&rset);
    FD_SET(sock, &rset);
    wset = rset;    //structure assignment ok

    //set socket nonblocking flag
    if( (flags = fcntl(sock, F_GETFL, 0)) < 0)
        return -1;

    if(fcntl(sock, F_SETFL, flags | O_NONBLOCK) < 0)
        return -1;

    //initiate non-blocking connect
    if( (ret = connect(sock, (struct sockaddr *)&sa, 16)) < 0 )
        if (errno != EINPROGRESS)
            return -1;

    if(ret == 0)    //then connect succeeded right away
        goto done;

    //we are waiting for connect to complete now
    if( (ret = select(sock + 1, &rset, &wset, NULL, (timeout) ? &ts : NULL)) < 0)
        return -1;
    if(ret == 0){   //we had a timeout
        errno = ETIMEDOUT;
        return -1;
    }

    //we had a positivite return so a descriptor is ready
    if (FD_ISSET(sock, &rset) || FD_ISSET(sock, &wset)){
        if(getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
            return -1;
    }else
        return -1;

    if(error){  //check if we had a socket error
        errno = error;
        return -1;
    }

done:
    //put socket back in blocking mode
    if(fcntl(sock, F_SETFL, flags) < 0)
        return -1;

    return 0;
}


/*
   ============================================================================
   ============================================================================
*/
int knocker_core_init (void)
{
#ifdef __WIN32_WINSOCK2__
  WORD winsock_version = MAKEWORD (2, 0);
#elif defined __WIN32__
  WORD winsock_version = MAKEWORD (1, 1);
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_init() called.\n");
#endif

#ifdef __WIN32__
  /* Start up the dreaded Winsock */
  if (WSAStartup (winsock_version, &knocker_core_wsadata) != 0)
    return -1;
#endif /* __WIN32__ */

  knocker_core_last_hostip = NULL;      /* string of the last resolved host ip address */
  knocker_core_last_hostname = NULL;    /* string of the last used host name */
  knocker_core_last_service = NULL;     /* string of the last service */

  return 0;
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_core_quit (void)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_quit() called.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: knocker_core_last_hostip is: %s, memory must be deallocated... ", knocker_core_last_hostip);
#endif
/*  FIXME 
    if (knocker_core_last_hostip != NULL)
    free (knocker_core_last_hostip); 
*/
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: knocker_core_last_hostname is: %s, memory must be deallocated... ", knocker_core_last_hostname);
#endif
/*  FIXME
    if (knocker_core_last_hostname != NULL)
    free (knocker_core_last_hostname); 
*/
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: knocker_core_last_service is: %s, memory must be deallocated... ", knocker_core_last_service);
#endif
/*  FIXME
    if (knocker_core_last_service != NULL)
    free (knocker_core_last_service); 
*/
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef __WIN32__
  /* Shut Winsock back down */
  WSACleanup ();
#endif /* __WIN32__ */
}


/*
   ============================================================================
   ============================================================================
*/
int knocker_core_init_portscan_data (knocker_core_portscan_data_t * data)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_init_portscan_data(...) called.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: initializing socket data with a call to knocker_core_init_socket_data()... ");
#endif

  knocker_core_init_socket_data (&data->socket);

#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: initializing port data with a call to knocker_core_init_port_data()... ");
#endif

  knocker_core_init_port_data (data->port);

#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: initializing host data with a call to knocker_core_init_host_data()... ");
#endif

  knocker_core_init_host_data (&data->host);
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_core_free_portscan_data (knocker_core_portscan_data_t * data)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_free_portscan_data(...) called\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: deallocating scoket data with a call to knocker_core_free_socket_data()... ");
#endif
  /* FIXME knocker_core_free_socket_data (&data->socket); */
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: deallocating port data with a call to knocker_core_free_port_data()... ");
#endif
  /* FIXME knocker_core_free_port_data (data->port); */
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif

#ifdef DEBUG
  fprintf (stderr, "debug: deallocating host data with a call to knocker_core_free_host_data()... ");
#endif
  /* FIXME knocker_core_free_host_data (&data->host); */
#ifdef DEBUG
  fprintf (stderr, "done.\n");
#endif
}


/*
   ============================================================================
   ============================================================================
*/
char *knocker_core_get_hostname (knocker_core_portscan_data_t * data)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_get_hostname (...) called\n");
#endif

  if (knocker_core_last_hostname == NULL)
    {
      knocker_core_last_hostname = malloc (1 + strlen (knocker_core_get_host_name_string (&data->host)));
    }
  else
    {
      knocker_core_last_hostname = realloc (knocker_core_last_hostname, 1 + strlen (knocker_core_get_host_name_string (&data->host)));

    }
#ifdef DEBUG
  fprintf (stderr, "debug: allocated %d bytes for knocker_core_last_hostname\n",
           1 + strlen (knocker_core_get_host_name_string (&data->host)));
  fprintf (stderr, "debug: calling knocker_core_get_host_name_string to get the hostname...\n");
  fprintf (stderr, "debug: knocker_core_get_host_name_string returned \"%s\" (%d bytes)\n",
           knocker_core_get_host_name_string (&data->host), strlen (knocker_core_get_host_name_string (&data->host)));
#endif


  return (strcpy (knocker_core_last_hostname, knocker_core_get_host_name_string (&data->host)));
}


/*
   ============================================================================
   ============================================================================
*/
char *knocker_core_get_hostip (knocker_core_portscan_data_t * data)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_get_hostip (...) called\n");
#endif

  if (knocker_core_last_hostip == NULL)
    {
      knocker_core_last_hostip = malloc (1 + strlen (knocker_core_get_host_ip_string (&data->host)));
    }
  else
    {
      knocker_core_last_hostip = realloc (knocker_core_last_hostip, 1 + strlen (knocker_core_get_host_ip_string (&data->host)));

    }
#ifdef DEBUG
  fprintf (stderr, "debug: allocated %d bytes for knocker_core_last_hostip\n", 1 + strlen (knocker_core_get_host_ip_string (&data->host)));
  fprintf (stderr, "debug: calling knocker_core_get_host_ip_string to get the host ip...\n");
  fprintf (stderr, "debug: knocker_core_get_host_ip_string returned \"%s\" (%d bytes)\n",
           knocker_core_get_host_ip_string (&data->host), strlen (knocker_core_get_host_ip_string (&data->host)));
#endif
  return (strcpy (knocker_core_last_hostip, knocker_core_get_host_ip_string (&data->host)));
}


/*
   ============================================================================
   ============================================================================
*/
char *knocker_core_get_service (unsigned int port, int protocol)
{
  int slenght;                  /* string lenght */
  char tmpstr[200];             /* That must be enought for a service name :-) */
  /* I must be paranoid */

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_get_service (...) called\n");
  fprintf (stderr, "debug: arguments passed port: %d, protocol: %d\n", port, protocol);
  fprintf (stderr, "debug: checking if passed protocol type is OK... ");
#endif

  if (protocol != PROTO_TCP)
    {
#ifdef DEBUG
      fprintf (stderr, " it is not TCP... \n");
#endif
      if (protocol != PROTO_UDP)
        {
#ifdef DEBUG
          fprintf (stderr, "nor UDP, returning NULL !!\n");
#endif
          return NULL;
        }
    }

#ifdef DEBUG
  fprintf (stderr, "Yes.\n");
#endif

  /* this functions returns the number of copied chars in tmpstr, if it is
     successfull, else -1 */
  slenght = knocker_core_getservbyport (tmpstr, port, protocol);

#ifdef DEBUG
  fprintf (stderr, "debug: %d bytes to be allocated for knocker_core_last_service\n", slenght + 1);
  fprintf (stderr, "debug: returned service by knocker_core_getservbyport is \"%s\", (%d bytes)\n", tmpstr, strlen (tmpstr));
#endif

  if (slenght == -1)
    {
      if (knocker_core_last_service == NULL)
        {
          knocker_core_last_service = malloc (strlen ("unknown") + 1);
          strcpy (knocker_core_last_service, "unknown");
        }
      else
        {
          knocker_core_last_service = realloc (knocker_core_last_service, strlen ("unknown") + 1);
          strcpy (knocker_core_last_service, "unknown");
        }
      return NULL;
    }

  if (knocker_core_last_service == NULL)
    {
      knocker_core_last_service = malloc (slenght + 1);
    }
  else
    {
      knocker_core_last_service = realloc (knocker_core_last_service, slenght + 1);

    }

  return (strcpy (knocker_core_last_service, tmpstr));
}


/*
   ============================================================================
   ============================================================================
*/
int knocker_core_validate_port_number (unsigned int port)
{
  if (port < 1)
    return FALSE;

  if (port > KNOCKER_MAX_PORT_NUMBER)
    return FALSE;

  return TRUE;
}



/*
   ============================================================================
   ============================================================================
*/
int knocker_core_portscan_tcp_connnect_block (knocker_core_portscan_data_t * data, unsigned int port)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_portscan_tcp_connnect (...) called\n");
  fprintf (stderr, "debug: connecting to port: %d\n", port);
#endif

  if (knocker_core_open_socket (&data->socket, PROTO_TCP) == KNOCKER_SOCKET_ERROR)
    {
#ifdef DEBUG
      fprintf (stderr, "debug: socket error, couldn't connect.\n");
#endif
      return -1;
    }

  data->host.sockaddr_in.sin_family = AF_INET;
  data->host.sockaddr_in.sin_port = htons (port);
  data->host.sockaddr_in.sin_addr = *((struct in_addr *) data->host.info->h_addr);
  memset (&(data->host.sockaddr_in.sin_zero), 0, 8);

  if (!connect (data->socket.fd, (struct sockaddr *) &data->host.sockaddr_in, sizeof (struct sockaddr)))
    /* here the port is open */
    {
      knocker_core_close_socket (&data->socket);
#ifdef DEBUG
      fprintf (stderr, "debug: connected to port: %d, port is open\n", port);
#endif
      return PORT_OPEN;
    }
#ifdef DEBUG
  fprintf (stderr, "debug: port: %d is closed\n", port);
#endif

  /* the socket must be closed even if the remote port is closed */
  knocker_core_close_socket (&data->socket);

  return (PORT_CLOSED);
}


/*
   ============================================================================
   ============================================================================
*/
int knocker_core_portscan_tcp_connnect (knocker_core_portscan_data_t * data, unsigned int port)
{
  int timeout=1; /* connect timeout */
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_portscan_tcp_connnect (...) called\n");
  fprintf (stderr, "debug: connecting to port: %d\n", port);
#endif

  if (knocker_core_open_socket (&data->socket, PROTO_TCP) == KNOCKER_SOCKET_ERROR)
    {
#ifdef DEBUG
      fprintf (stderr, "debug: socket error, couldn't connect.\n");
#endif
      return -1;
    }

  data->host.sockaddr_in.sin_family = PF_INET;
  data->host.sockaddr_in.sin_port = htons (port);
  data->host.sockaddr_in.sin_addr = *((struct in_addr *) data->host.info->h_addr);
  memset (&(data->host.sockaddr_in.sin_zero), 0, 8);


  if (_connect_nonblocking (data->socket.fd, data->host.sockaddr_in, timeout) != -1)
    /* here the port is open */
    {
      knocker_core_close_socket (&data->socket);
#ifdef DEBUG
      fprintf (stderr, "debug: connected to port: %d, port is open\n", port);
#endif
      return PORT_OPEN;
    }
#ifdef DEBUG
  fprintf (stderr, "debug: port: %d is closed\n", port);
#endif

  /* the socket must be closed even if the remote port is closed */
  knocker_core_close_socket (&data->socket);

  return (PORT_CLOSED);
}




/*
   ============================================================================
   ============================================================================
*/
char *knocker_core_resolve_host (knocker_core_portscan_data_t * data, const char *hostname)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_resolve_host (...) called.\n");
#endif

  if (knocker_core_gethostbyname (&data->host, hostname) == -1)
    return NULL;
  else
    return (data->host.ip);
}


/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_init_host_data (knocker_core_host_t * host)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_init_host_data (...) called.\n");
#endif

  knocker_core_set_host_name_string (host, NULL);
  knocker_core_set_host_ip_string (host, NULL);

  return 0;
}



/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_free_host_data (knocker_core_host_t * host)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_free_host_data (...) called.\n");
#endif

/* FIXME deliberatelly not freeing here to avoid crashdump
  knocker_core_free_host_name_string (host);
  knocker_core_free_host_ip_string (host); */
}



/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_init_port_data (knocker_core_port_t * port)
{
  int i;

  for (i = 0; i < KNOCKER_MAX_PORT_NUMBER; i++)
    {
      port[i].number = 0;
      port[i].status = PORT_NONE;
      port[i].protocol = PROTO_NONE;
      port[i].service = NULL;
    }

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_free_port_data (knocker_core_port_t * port)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_free_port_data (...) called.\n");
#endif


  int i;

  for (i = 0; i < KNOCKER_MAX_PORT_NUMBER; i++)
    {
      port[i].number = 0;
      port[i].status = PORT_NONE;
      port[i].protocol = PROTO_NONE;

      if (port[i].service != NULL)
        {
	  /* FIXME deliberatelly not freeing here to avoid crash dump */	
          /* free (port[i].service); */
        }
    }
}


/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_init_socket_data (knocker_core_socket_t * sock)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_init_socket_data (...) called.\n");
#endif


  if (sock->active == TRUE)
    knocker_core_close_socket (sock);

  sock->protocol = PROTO_NONE;
  sock->active = FALSE;

  return 0;
}


/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_free_socket_data (knocker_core_socket_t * sock)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_free_socket_data (...) called.\n");
#endif

  knocker_core_init_socket_data (sock);
}

/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_open_socket (knocker_core_socket_t * sock, int protocol)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_open_socket (...) called.\n");
#endif
  if (protocol == PROTO_TCP)
    {
      if ((sock->fd = socket (AF_INET, SOCK_STREAM, 0)) == KNOCKER_SOCKET_ERROR)
        {
#ifdef DEBUG
          fprintf (stderr, "debug: couldn't open the socket: ");
          perror ("socket");
#endif
          return -1;
        }
    }
  else if (protocol == PROTO_UDP)
    {
      if ((sock->fd = socket (AF_INET, SOCK_DGRAM, 0)) == KNOCKER_SOCKET_ERROR)
        {
#ifdef DEBUG
          fprintf (stderr, "debug: couldn't open the socket: ");
          perror ("socket");
#endif
          return -1;
        }
    }
  else
    return -1;

  sock->protocol = protocol;
  sock->active = TRUE;

#ifdef DEBUG
  fprintf (stderr, "debug: socket open succesfully.");
#endif

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_close_socket (knocker_core_socket_t * sock)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_close_socket (...) called.\n");
#endif

  if (sock->active == FALSE)
    return;

#ifdef __WIN32__
  closesocket (sock->fd);
#else
  close (sock->fd);
#endif

  sock->active = FALSE;
  sock->protocol = PROTO_NONE;

#ifdef DEBUG
  fprintf (stderr, "debug: socket closed.\n");
#endif

}


/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_gethostbyname (knocker_core_host_t * hinfo, const char *hostname)
{
  struct hostent *htemp;
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_core_gethostbyname (...) called.\n");
#endif

  htemp = gethostbyname (hostname);

  if (htemp == NULL)
    return -1; 
	
  
  hinfo->info = gethostbyname (hostname);

  knocker_core_set_host_name_string (hinfo, hostname);
  knocker_core_set_host_ip_string (hinfo, inet_ntoa (*(struct in_addr *) *hinfo->info->h_addr_list));

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_getservbyport (char *service, unsigned int port, int protocol)
{
  struct servent *service_st;

  if (protocol == PROTO_TCP)
    {
      service_st = getservbyport (htons (port), "tcp");
    }
  else if (protocol == PROTO_UDP)
    {
      service_st = getservbyport (htons (port), "udp");
    }
  else
    return -1;


  if (!service_st)
    {
      /*strcpy (service, "unknown"); */
      service = NULL;
      return -1;
    }
  else
    {
      strcpy (service, service_st->s_name);
    }

  return (strlen (service_st->s_name));
}




/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_set_host_name_string (knocker_core_host_t * hinfo, const char *hostname)
{
  if (hostname == NULL)
    {
      hinfo->name = NULL;
      return 0;
    }

  /*
     If the hostname in the hinfo structure is NULL
     we copy the passed hostname there.
   */
  if (hinfo->name == NULL)
    {
      hinfo->name = malloc (strlen (hostname) + 1);
      strcpy (hinfo->name, hostname);
    }
  else                          /* if the hinfo->name is used already */
    {
      /*
         if the hostname in the hinfo structure is not the
         same as the passed hostname, we just update it.
       */
      if (strcmp (hinfo->name, hostname))
        {
          hinfo->name = realloc (hinfo->name, strlen (hostname) + 1);
          strcpy (hinfo->name, hostname);

        }
    }

  return 0;
}


/*
   ============================================================================
   ============================================================================
*/
static int knocker_core_set_host_ip_string (knocker_core_host_t * hinfo, const char *hostip)
{
  if (hostip == NULL)
    {
      hinfo->ip = NULL;
      return 0;
    }

  /*
     If the hostname in the hinfo structure is NULL
     we copy the passed hostip there.
   */
  if (hinfo->ip == NULL)
    {
      hinfo->ip = malloc (strlen (hostip) + 1);
      strcpy (hinfo->ip, hostip);
    }
  else                          /* if the hinfo->ip is used already */
    {
      /*
         if the hostname in the hinfo structure is not the
         same as the passed hostip, we just update it.
       */
      if (strcmp (hinfo->ip, hostip))
        {
          hinfo->ip = realloc (hinfo->ip, strlen (hostip) + 1);
          strcpy (hinfo->ip, hostip);

        }
    }

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
static char *knocker_core_get_host_name_string (knocker_core_host_t * hinfo)
{
  return (hinfo->name);
}

/*
   ============================================================================
   ============================================================================
*/
static char *knocker_core_get_host_ip_string (knocker_core_host_t * hinfo)
{
  return (hinfo->ip);
}


/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_free_host_name_string (knocker_core_host_t * hinfo)
{
  if (hinfo->name != NULL)
    {
      /* FIXME DELIBERATELLY NOT FREEING HERE TO AVOID CRASHDUMMPS    
      free (hinfo->name);
      knocker_core_set_host_name_string (hinfo, NULL); 
      */
    }
}

/*
   ============================================================================
   ============================================================================
*/
static void knocker_core_free_host_ip_string (knocker_core_host_t * hinfo)
{
  if (hinfo->ip != NULL)
    {
      /* FIXME DELIBERATELLY NOT FREEING HERE TO AVOID CHRASHDUMPS 
      free (hinfo->ip);
      knocker_core_set_host_ip_string (hinfo, NULL);
      */
    }

}
