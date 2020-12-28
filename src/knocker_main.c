/* knocker version 0.7.1
 * Release date: 24 May 2002
 *
 * Project homepage: http://knocker.sourceforge.net
 *
 * Copyright 2001,2002 Gabriele Giorgetti <g.gabriele79@genie.it>
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knocker_log.h"
#include "knocker_output.h"
#include "knocker_term.h"
#include "knocker_args.h"
#include "knocker_user.h"
#include "knocker_conf.h"
#include "knocker_core.h"
#include "knocker_time.h"
#include "knocker_led.h"
#include "knocker_services.h"

#include <time.h>

#include "knuckles.h"

int total_open_ports = 0;
int total_scanned_ports = 0;

double elapsed_time;

knocker_core_portscan_data_t pscan_data;

/*
   ============================================================================
   ============================================================================
*/
static void init (int argc, char *argv[])
{
  knocker_core_init ();

  if (init_knocker_core_services_db () < 0)
    {
      fprintf (stderr, "%s: Error allocating services strings memory. Fatal.\n", PACKAGE);
      exit (EXIT_FAILURE);
    }

  knocker_user_init (&knocker_user);

  knocker_args_init (&knocker_args, FALSE, FALSE, TRUE);

  knocker_args_parse (&knocker_args, argc, argv);

  if (knocker_conf_parse () < 0)
    /* write a default conf file for the user if it is not already there. */
    knocker_conf_write_default ();

  knocker_core_init_portscan_data (&pscan_data);

  if (knocker_args.fency)
    knocker_term_clear ();

  knocker_output_open ();

  knocker_term_fprintf (stdout, "\n");

  /* open and initialize log file if needed */
  if (knocker_log_open (knocker_args.lfname) < 0)
    {
      fprintf (stderr, "%s: error, couldn't open the log file (%s)\n", PACKAGE, KNOCKER_LOG_FILE);
      fprintf (stderr, "(You might not have write permission on the current directory.)\n");
      fprintf (stderr, "Knocker portscan aborted.\n");

      knocker_args_free (&knocker_args);
      knocker_core_free_portscan_data (&pscan_data);
      knocker_core_quit ();
      exit (EXIT_FAILURE);
    }
}

/*
   ============================================================================
   ============================================================================
*/
static void quit (void)
{
  knocker_log_close ();

  knocker_args_free (&knocker_args);

  knocker_user_free (&knocker_user);

  knocker_core_free_portscan_data (&pscan_data);

  free_knocker_core_services_db ();

#ifdef        __WIN32__
  if ((knocker_args.win32_frontend) && (!knocker_args.quiet))
    {
      system ("PAUSE");
    }
#endif

  /* knocker_led_reset(); Not ready for leds Yet */

  knocker_term_reset ();

  knocker_core_quit ();
}

/*
   ============================================================================
   ============================================================================
*/
static void resolve (void)
{
  if (knocker_core_resolve_host (&pscan_data, knocker_args.hname) == NULL)
    {
      knocker_output_resolve_error (knocker_args.hname);
      knocker_log_resolve_error (knocker_args.hname);
      quit ();
      exit (EXIT_FAILURE);
    }

  knocker_core_get_hostname (&pscan_data);
  knocker_core_get_hostip (&pscan_data);

  knocker_output_host_info (knocker_core_last_hostname, knocker_core_last_hostip);
  knocker_log_host_info (knocker_core_last_hostname, knocker_core_last_hostip);
}




/*
   ============================================================================
   ============================================================================
*/
static void portscan (void)
{

  knocker_term_fflush (stdout);


  if (knocker_args.port != 0)
    {

      knocker_output_ports_info (knocker_args.port, knocker_args.port);
      knocker_log_ports_info (knocker_args.port, knocker_args.port);

      knocker_user_write_lastscan (&knocker_user, &knocker_args);

      knocker_time_start_timer ();

      if (knocker_core_portscan_tcp_connnect (&pscan_data, knocker_args.port) == PORT_OPEN)
        {

#ifdef        __WIN32__

#else
          knocker_core_get_service (knocker_args.port, PROTO_TCP);
#endif
          knocker_output_open_port (knocker_args.port, knocker_core_last_service);
          knocker_log_open_port (knocker_args.port, knocker_core_last_service);
        }

      elapsed_time = knocker_time_get_ticks ();

      total_scanned_ports = 1;
      return;
    }

  else if ((knocker_args.sport == 0) && (knocker_args.eport == 0))
    {
      int port;

      knocker_args.sport = 1;
      knocker_args.eport = KNOCKER_DEFAULT_PORT_RANGE;

      knocker_output_ports_info (knocker_args.sport, knocker_args.eport);
      knocker_log_ports_info (knocker_args.sport, knocker_args.eport);

      knocker_user_write_lastscan (&knocker_user, &knocker_args);

      knocker_time_start_timer ();

      for (port = knocker_args.sport; port <= knocker_args.eport; port++)
        {
          if (knocker_core_portscan_tcp_connnect (&pscan_data, port) == PORT_OPEN)
            {
              total_open_ports++;

#ifdef        __WIN32__

              knocker_core_services_db_get_service (port, PROTO_TCP);
#else
              if (knocker_core_get_service (port, PROTO_TCP) == NULL)
                {
                  knocker_core_services_db_get_service (port, PROTO_TCP);
                }
#endif

              knocker_term_fflush (stdout);

              knocker_output_open_port (port, knocker_core_last_service);
              knocker_log_open_port (port, knocker_core_last_service);

            }
        }

      elapsed_time = knocker_time_get_ticks ();

      total_scanned_ports = port;
      return;
    }

  knocker_output_ports_info (knocker_args.sport, knocker_args.eport);
  knocker_log_ports_info (knocker_args.sport, knocker_args.eport);

  if ((knocker_args.sport == knocker_args.eport) && (knocker_args.sport != 0) && (knocker_args.eport != 0))
    {
      int port = knocker_args.sport;

      knocker_user_write_lastscan (&knocker_user, &knocker_args);

      knocker_time_start_timer ();

      if (knocker_core_portscan_tcp_connnect (&pscan_data, port) == PORT_OPEN)
        {
#ifdef        __WIN32__

          knocker_core_services_db_get_service (port, PROTO_TCP);
#else
          if (knocker_core_get_service (port, PROTO_TCP) == NULL)
            {
              knocker_core_services_db_get_service (port, PROTO_TCP);
            }
#endif

          knocker_output_open_port (port, knocker_core_last_service);
          knocker_log_open_port (port, knocker_core_last_service);
        }

      elapsed_time = knocker_time_get_ticks ();

      total_scanned_ports = 1;
      return;
    }

  else if (knocker_args.sport > knocker_args.eport)
    {
      int port = 0;             /* avaoid unitialization warning */

      knocker_user_write_lastscan (&knocker_user, &knocker_args);

      knocker_time_start_timer ();

      for (port = knocker_args.sport; port >= knocker_args.eport; port--)
        {
          if (knocker_core_portscan_tcp_connnect (&pscan_data, port) == PORT_OPEN)
            {
              total_open_ports++;

#ifdef        __WIN32__
              knocker_core_services_db_get_service (port, PROTO_TCP);
#else
              if (knocker_core_get_service (port, PROTO_TCP) == NULL)
                {
                  knocker_core_services_db_get_service (port, PROTO_TCP);
                }
#endif

              knocker_output_open_port (port, knocker_core_last_service);
              knocker_log_open_port (port, knocker_core_last_service);
            }

        }
      elapsed_time = knocker_time_get_ticks ();

      total_scanned_ports = knocker_args.sport - port;
      return;
    }

  else
    {
      int port;

      knocker_user_write_lastscan (&knocker_user, &knocker_args);

      knocker_time_start_timer ();

      for (port = knocker_args.sport; port <= knocker_args.eport; port++)
        {
          /* Not ready yet for these stuffs
             knocker_led_sequence();
             usleep(10000); / usleep is deprecated, use nanosleep instead 
             knocker_time_delay(10);
           */

          if (knocker_core_portscan_tcp_connnect (&pscan_data, port) == PORT_OPEN)
            {
              total_open_ports++;

#ifdef        __WIN32__
              knocker_core_services_db_get_service (port, PROTO_TCP);
#else
              if (knocker_core_get_service (port, PROTO_TCP) == NULL)
                {
                  knocker_core_services_db_get_service (port, PROTO_TCP);
                }
#endif

              knocker_output_open_port (port, knocker_core_last_service);
              knocker_log_open_port (port, knocker_core_last_service);
            }
        }

      elapsed_time = knocker_time_get_ticks ();

      total_scanned_ports = port - knocker_args.sport;
      return;
    }
  return /* it should be never reached */ ;
}




/*
   ============================================================================
   ============================================================================
*/
static void results (void)
{
  char timestr[80];

  elapsed_time = elapsed_time / 1000;
  sprintf (timestr, "%.2f", elapsed_time);

  knocker_output_results (knocker_core_last_hostname, knocker_core_last_hostip, total_scanned_ports, total_open_ports, timestr);
  knocker_log_results    (knocker_core_last_hostname, knocker_core_last_hostip, total_scanned_ports, total_open_ports, timestr);
}


/*
   ============================================================================
   ============================================================================
*/
int main (int argc, char *argv[])
{
  init (argc, argv);

  atexit (quit);

  resolve ();

  portscan ();

  results ();

  return (EXIT_SUCCESS);
}
