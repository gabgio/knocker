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

#ifndef _KNOCKER_CORE_H_
#define _KNOCKER_CORE_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifndef PACKAGE
#define PACKAGE "knocker"
#endif
#ifndef VERSION
#define VERSION _KNOCKER_CORE_VERSION_
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef        __WIN32__             /* Use Winsock Version 1.1 */
                                    /* To be linked with -lwsock32 */
#include <windows.h>
#include <winsock.h>

#elif defined __WIN32_WINSOCK2__    /* Use Winsock Version 2.0 */
                                    /* To be linked with -lws2_32 */
#define       __WIN32__
#include <windows.h>
#include <winsock2.h>

#else

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#endif       /* __WIN32__ */


/* If in trouble .... :-) */
/* #define DEBUG */
/* and run knocker in quiet mode to se debug output only */

#ifndef _KNOCKER_CORE_VERSION_
#define _KNOCKER_CORE_VERSION_      "0.8.0"
#endif
#ifndef _KNOCKER_CORE_RELEASE_DATE_
#define _KNOCKER_CORE_RELEASE_DATE_ "28 December 2020"
#endif
#ifndef _KNOCKER_CORE_HOMEPAGE_
#define _KNOCKER_CORE_HOMEPAGE_     "https://knocker.sourceforge.io"
#endif
#ifndef _KNOCKER_CORE_AUTHOR_
#define _KNOCKER_CORE_AUTHOR_       "Gabriele Giorgetti"
#endif
#ifndef _KNOCKER_CORE_AUTHOR_EMAIL_
#define _KNOCKER_CORE_AUTHOR_EMAIL_ "<g.giorgetti@gmail.com>"
#endif

#define KNOCKER_DEFAULT_PORT_RANGE 1024  /* by default scan from 1 to 1024 */
#define KNOCKER_MAX_PORT_NUMBER    65535 /* max allowed port number */


#ifndef FALSE
enum
{ FALSE, TRUE };
#endif

#ifndef EXIT_FAILURE
enum
{ EXIT_SUCCESS, EXIT_FAILURE };
#endif

enum
{ PORT_NONE, PORT_CLOSED, PORT_OPEN };

enum
{ PROTO_NONE, PROTO_UDP, PROTO_TCP };

#ifdef __WIN32__
#define KNOCKER_SOCKET_ERROR       INVALID_SOCKET
#else
#define KNOCKER_SOCKET_ERROR       -1    /* in UNIX socket errors are returned with -1 */
#endif /* __WIN32__ */

typedef struct {
#ifdef __WIN32__
  SOCKET                           fd;           /* Winsocket socket */
#else
  int                              fd;           /* socket file descriptor */
#endif /* __WIN32__ */
  int                              active;       /* if socket is connected or not, TRUE or FALSE */
  int                              protocol;     /* protocol PROTO_NONE, PROTO_UDP, PROTO_TCP   */
} knocker_core_socket_t;

typedef struct {
  unsigned int                     number;       /* port number */
  char                             *service;     /* associated service name */
  int                              status;       /* port status, PORT_NONE PORT_OPEN or PORT_CLOSED */
  int                              protocol;     /* protocol PROTO_NONE, PROTO_UDP, PROTO_TCP   */
} knocker_core_port_t;

/*
typedef struct {
  char                             *servname;
  char                             *servinfo;
} knocker_core_services_db_t;
*/

typedef struct {
  struct hostent                   *info;        /* hostent structure */
  struct sockaddr_in               sockaddr_in;  /* sockaddr_in structure */
  char                             *name;        /* hostname string   */
  char                             *ip;          /* host IP address string */
} knocker_core_host_t;

typedef struct {
  knocker_core_socket_t            socket;
  knocker_core_port_t              port[KNOCKER_MAX_PORT_NUMBER];
  knocker_core_host_t              host;
} knocker_core_portscan_data_t;


#ifdef __WIN32__
 WSADATA knocker_core_wsadata;
#endif /* __WIN32__ */

#define knocker_socket_t        knocker_core_socket_t
#define knocker_port_t          knocker_core_port_t
#define knocker_host_t          knocker_core_host_t
#define knocker_portscan_data_t knocker_core_portscan_data_t

static const char knocker_core_version[]      = _KNOCKER_CORE_VERSION_;
static const char knocker_core_release_date[] = _KNOCKER_CORE_RELEASE_DATE_;
static const char knocker_core_homepage[]     = _KNOCKER_CORE_HOMEPAGE_;
static const char knocker_core_author[]       = _KNOCKER_CORE_AUTHOR_;
static const char knocker_core_author_email[] = _KNOCKER_CORE_AUTHOR_EMAIL_;

/* allocated and deallocated within knocker_core_init, knocker_core_quit */
extern char *knocker_core_last_hostip;   /* string of the last resolved host ip address */
extern char *knocker_core_last_hostname; /* string of the last used host name */
extern char *knocker_core_last_service;  /* string of the last service */


int   knocker_core_init ( void );
void  knocker_core_quit ( void );


int   knocker_core_portscan_tcp_connnect (knocker_core_portscan_data_t *data, unsigned int port);

/* Initialize the knocker_core_portscan_data_t structure data */
int   knocker_core_init_portscan_data (knocker_core_portscan_data_t *data);

/* Frees the the knocker_core_portscan_data_t structure data */
void  knocker_core_free_portscan_data (knocker_core_portscan_data_t *data);

/* Returns FALSE if port is > than KNOCKER_MAX_PORT_NUMBER and < 1 */
int   knocker_core_validate_port_number (unsigned int port);

/* returns host ip address on success, NULL on failure */
char *knocker_core_resolve_host (knocker_core_portscan_data_t *data, const char *hostname);

/* return the hostname string from the structure */
char *knocker_core_get_hostname (knocker_core_portscan_data_t *data);

/* return the host ip string from the structure */
char *knocker_core_get_hostip   (knocker_core_portscan_data_t *data);

/* return the service name string using getservbyport */
char *knocker_core_get_service (unsigned int port, int protocol);

/* Functions used internally
---- ------------------------------------------------------------------------------------------
static int  knocker_core_init_port_data   (knocker_core_port_t *port);
static void knocker_core_free_port_data   (knocker_core_port_t *port);

static int  knocker_core_init_socket_data   (knocker_core_socket_t *sock);
static void knocker_core_free_socket_data   (knocker_core_socket_t *sock);
static int  knocker_core_open_socket   (knocker_core_socket_t *sock, int protocol);
static void knocker_core_close_socket  (knocker_core_socket_t *sock);

static int  knocker_core_init_host_data   (knocker_core_host_t *host);
static void knocker_core_free_host_data   (knocker_core_host_t *host);

static int   knocker_core_gethostbyname    (knocker_core_host_t *hinfo, const char *hostname);
static int   knocker_core_getservbyport    (char *service, unsigned int port, int protocol);

static char *knocker_core_get_host_name_string (knocker_core_host_t *hinfo);
static char *knocker_core_get_host_ip_string   (knocker_core_host_t *hinfo);
static int  knocker_core_set_host_name_string  (knocker_core_host_t *hinfo, const char *hostname);
static int  knocker_core_set_host_ip_string    (knocker_core_host_t *hinfo, const char *hostip);
static void knocker_core_free_host_name_string (knocker_core_host_t *hinfo);
static void knocker_core_free_host_ip_string   (knocker_core_host_t *hinfo);
----- ------------------------- ---------------------------------------------------------------
*/

#endif /* _KNOCKER_CORE_H_ */

