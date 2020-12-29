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


#include "knocker_core.h"
#include "knocker_args.h"
#include "knocker_user.h"
#include "knocker_conf.h"
#include "knocker_log.h"

knocker_args_t knocker_args; /* command line arguments structure */

/* used internally by knocker_args_parse */
static void knocker_args_validate (knocker_args_t * args, int argc, char *argv[]);

static int _have_last_host = 0; /* tells if we've got the host with the --last-host option */



static void print_version_info (void)
{
#ifdef        __WIN32__
  fprintf (stdout, "%s %s-Win32 (%s)\n", PACKAGE, VERSION, knocker_core_release_date);
#else
  fprintf (stdout, "%s %s (%s)\n", PACKAGE, VERSION, knocker_core_release_date);
#endif
}


static void print_help_info (void)
{
#ifdef        __WIN32__
  fprintf (stdout, "%s, the net portscanner. Version %s-Win32 (%s)\n", PACKAGE, VERSION, knocker_core_release_date);
#else
  fprintf (stdout, "%s, the net portscanner. Version %s (%s)\n", PACKAGE, VERSION, knocker_core_release_date);
#endif

  fprintf (stdout, "\n");
  fprintf (stdout, "Usage: %s %s <HOST> [OPTIONS]\n", PACKAGE, HOST_LONG_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "Example: %s %s 192.168.0.1 %s 1 %s 1024\n", PACKAGE, HOST_SHORT_OPT, START_PORT_SHORT_OPT, END_PORT_SHORT_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "Required options:\n");
  fprintf (stdout, "      %s,  %s              host name or numeric Internet address\n", HOST_SHORT_OPT, HOST_LONG_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "Common options:\n");
  fprintf (stdout, "      %s,  %s              single port number (for one port scans only)\n", SINGLE_PORT_SHORT_OPT,
           SINGLE_PORT_LONG_OPT);
  fprintf (stdout, "      %s, %s        port number to begin the scan from\n", START_PORT_SHORT_OPT, START_PORT_LONG_OPT);
  fprintf (stdout, "      %s, %s          port number to end the scan at\n", END_PORT_SHORT_OPT, END_PORT_LONG_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "Extra options:\n");
  fprintf (stdout, "      %s,  %s             quiet mode (no console output, logs to file)\n", QUIET_MODE_SHORT_OPT, QUIET_MODE_LONG_OPT);
  fprintf (stdout, "      %s, %s <logfile> log scan results to the specified file\n", ENABLE_LOGFILE_SHORT_OPT, ENABLE_LOGFILE_LONG_OPT);
  fprintf (stdout, "      %s, %s          disable fency output\n", NO_FENCY_SHORT_OPT, NO_FENCY_LONG_OPT);
  fprintf (stdout, "      %s, %s         disable colored output\n", NO_COLORS_SHORT_OPT, NO_COLORS_LONG_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "      %s              let you configure %s\n", CONFIGURE_LONG_OPT, PACKAGE);
  fprintf (stdout, "\n");
  fprintf (stdout, "Info options:\n");
  fprintf (stdout, "      %s,  %s              display this help and exit\n", HELP_SHORT_OPT, HELP_LONG_OPT);
  fprintf (stdout, "      %s,  %s           output version information and exit\n", VERSION_SHORT_OPT, VERSION_LONG_OPT);
  fprintf (stdout, "\n");
  fprintf (stdout, "SEE THE MAN PAGE FOR MORE DESCRIPTIONS, AND EXAMPLES\n");
  fprintf (stdout, "Report bugs to %s.\n", knocker_core_author_email);
}



int knocker_args_init (knocker_args_t * args, int logfile, int quiet, int colors)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_args_init() called.\n");
#endif

  args->hname = NULL;
  args->hip = NULL;
  args->lfname = NULL;
  args->port = 0;
  args->sport = 0;
  args->eport = 0;
  args->logfile = logfile;
  args->quiet = quiet;
  args->colors = colors;
  args->fency = TRUE;           /* true by default */

  return 0;
}


void knocker_args_free (knocker_args_t * args)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_args_free() called.\n");
#endif
/*
  if (args->hname != NULL)
    free (args->hname);

  if (args->lfname != NULL)
    free (args->lfname);

  if (args->hip != NULL)
    free (args->hip);
    */
  /* deliberatelly not freeing data to avoid crash dumps ! */
}


/*
int  knocker_args_argument (knocker_args_t *args, unsigned short argument)
{

}
*/


int knocker_args_parse (knocker_args_t * args, int argc, char *argv[])
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_args_parse() called.\n");
#endif
  int i;

  if (argv[1] == NULL)
    {
      fprintf (stderr, "%s: no arguments given\n", PACKAGE);
      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
      exit (EXIT_FAILURE);
    }

  for (i = 1; i <= argc - 1; i++)
    {
      if ((!strcmp (argv[i], VERSION_SHORT_OPT)) || (!strcmp (argv[i], VERSION_LONG_OPT)))
        {
          print_version_info ();
          exit (EXIT_SUCCESS);
        }
      else if ((!strcmp (argv[i], HELP_SHORT_OPT)) || (!strcmp (argv[i], HELP_LONG_OPT)))
        {
          print_help_info ();
          exit (EXIT_SUCCESS);
        }
      else if (!strcmp (argv[i], CONFIGURE_LONG_OPT))
        {
          knocker_conf_configure ();
          exit (EXIT_SUCCESS);
        }
      else if ((!strcmp (argv[i], NO_FENCY_SHORT_OPT)) || (!strcmp (argv[i], NO_FENCY_LONG_OPT)))
        {
          /* Disable fency output */
          args->fency = FALSE;
        }
      else if ((!strcmp (argv[i], NO_COLORS_SHORT_OPT)) || (!strcmp (argv[i], NO_COLORS_LONG_OPT)))
        {
          /* Disable colored output */
          args->colors = FALSE;
        }
      else if ((!strcmp (argv[i], ENABLE_LOGFILE_SHORT_OPT)) || (!strcmp (argv[i], ENABLE_LOGFILE_LONG_OPT)))
        {
          if (++i == argc)
            {
              fprintf (stderr, "%s: error, no logfile given\n", PACKAGE);
              fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }

          /* allocate space and set the logfile string arg */
          args->lfname = realloc (args->lfname, strlen (argv[i]) + 1);
          strcpy (args->lfname, argv[i]);

          /* log scan results to file */
          args->logfile = TRUE;
        }
      else if ((!strcmp (argv[i], QUIET_MODE_SHORT_OPT)) || (!strcmp (argv[i], QUIET_MODE_LONG_OPT)))
        {
          /* Enable quiet mode, disable stdout output, and log result to file */
          args->quiet = TRUE;
          args->colors = FALSE;
          args->logfile = TRUE;
        }
      else if ((!strcmp (argv[i], HOST_SHORT_OPT)) || (!strcmp (argv[i], HOST_LONG_OPT)))
        {
          if (!_have_last_host) /* If we haven't got the host to scan yet we check  and get it if the user has passed it */
            {
              if (++i == argc)
                {
                  fprintf (stderr, "%s: error, no host to scan given\n", PACKAGE);
                  fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
                  knocker_args_free (args);
                  exit (EXIT_FAILURE);
                }
              /* allocate space and set the hostname string arg */
              args->hname = realloc (args->hname, strlen (argv[i]) + 1);
              strcpy (args->hname, argv[i]);
            }
        }

      else if ((!strcmp (argv[i], SINGLE_PORT_SHORT_OPT)) || (!strcmp (argv[i], SINGLE_PORT_LONG_OPT)))
        {
          if (++i == argc)
            {
              fprintf (stderr, "%s: error, no port number given\n", PACKAGE);
              fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
          /* set the single port number for the one-port-only-scan */
          args->port = atoi (argv[i]);

          if (!knocker_core_validate_port_number (args->port))
            {
              fprintf (stderr, "%s: error, invalid port number `%d' given\n", PACKAGE, args->port);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
        }

      else if ((!strcmp (argv[i], START_PORT_SHORT_OPT)) || (!strcmp (argv[i], START_PORT_LONG_OPT)))
        {
          if (++i == argc)
            {
              fprintf (stderr, "%s: error, no port number, where to start the scan from, given\n", PACKAGE);
              fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
          /* set the start port number */
          args->sport = atoi (argv[i]);

          if (!knocker_core_validate_port_number (args->sport))
            {
              fprintf (stderr, "%s: error, invalid start port number `%d' given\n", PACKAGE, args->sport);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
        }
      else if ((!strcmp (argv[i], END_PORT_SHORT_OPT)) || (!strcmp (argv[i], END_PORT_LONG_OPT)))
        {
          if (++i == argc)
            {
              fprintf (stderr, "%s: error, no port number, where to scan to, given\n", PACKAGE);
              fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
          /* set the end port number */
          args->eport = atoi (argv[i]);

          if (!knocker_core_validate_port_number (args->eport))
            {
              fprintf (stderr, "%s: error, invalid end port number `%d' given\n", PACKAGE, args->eport);
              knocker_args_free (args);
              exit (EXIT_FAILURE);
            }
        }
      else if ((!strcmp (argv[i], WIN32_FRONTEND_SHORT_OPT)) || (!strcmp (argv[i], WIN32_FRONTEND_LONG_OPT)))
        {
          /* Disable colored output */
          args->win32_frontend = TRUE;
        }
      else
        {
          fprintf (stderr, "%s: invalid argument given: '%s'\n", PACKAGE, argv[i]);
          fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
          knocker_args_free (args);
          exit (EXIT_FAILURE);
        }

    }                           /* end of for loop */

  knocker_args_validate (args, argc, argv);

  return 0;
}


static void knocker_args_validate (knocker_args_t * args, int argc, char *argv[])
{
  int we_havegot_host = 0;
  int we_havegot_sp = 0;
  int we_havegot_ep = 0;
  int i;

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_args_validate() called.\n");
#endif

  for (i = 1; i <= argc - 1; i++)
    {
      if ((!strcmp (argv[i], HOST_SHORT_OPT)) || (!strcmp (argv[i], HOST_LONG_OPT)) )
        {
          we_havegot_host = 1;
        }
      if ((!strcmp (argv[i], START_PORT_SHORT_OPT)) || (!strcmp (argv[i], START_PORT_LONG_OPT)))
        we_havegot_sp = 1;
      if ((!strcmp (argv[i], END_PORT_SHORT_OPT)) || (!strcmp (argv[i], END_PORT_LONG_OPT)))
        we_havegot_ep = 1;
    }

  if (!we_havegot_host)         /* if HOST_SHORT_OPT or HOST_LONG_OPT is not the args */
    {
      fprintf (stderr, "%s: error, no host to scan given\n", PACKAGE);
      fprintf (stderr, "You must provide a host to scan with 'the %s <host>' or '%s <host>' option.\n", HOST_LONG_OPT, HOST_SHORT_OPT);
      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
      //knocker_args_free (args);
      exit (EXIT_FAILURE);
    }

  if ((we_havegot_sp) && (!we_havegot_ep))
    {
      fprintf (stderr, "%s: error, start port number given but no end port number. \n", PACKAGE);
      fprintf (stderr, "You must provide both a port number where to start the scan from and end\n");
      fprintf (stderr, "the scan to: %s <PORT> %s <PORT>\n", START_PORT_LONG_OPT, END_PORT_LONG_OPT);
      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
      //knocker_args_free (args);
      exit (EXIT_FAILURE);

    }
  if ((!we_havegot_sp) && (we_havegot_ep))
    {
      fprintf (stderr, "%s: error, end port number given but no start port number. \n", PACKAGE);
      fprintf (stderr, "You must provide both a port number where to start the scan from and end\n");
      fprintf (stderr, "the scan to: %s <PORT> %s <PORT>\n", START_PORT_LONG_OPT, END_PORT_LONG_OPT);
      fprintf (stderr, "Try `%s %s' for more information.\n", PACKAGE, HELP_LONG_OPT);
      //knocker_args_free (args);
      exit (EXIT_FAILURE);

    }

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_args_validate() return.\n");
#endif

}
