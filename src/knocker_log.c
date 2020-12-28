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

#include "knocker_core.h"
#include "knocker_log.h"
#include "knocker_args.h"
#include "knocker_user.h"
#include "knocker_time.h"

const char knocker_log_header[] =
  "+-----------------------------------------------------------------------------+\n|--=| k n o c k e r -- t h e -- n e t -- p o r t s c a n n e r |=-=[logfile]=-|\n+-----------------------------------------------------------------------------+\n";

char *knocker_time;

/*
   ============================================================================
   ============================================================================
*/
int knocker_log_open (const char *filename)
{
  time_t timenow;

  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return 0;

  if (filename == NULL)
    knocker_log_fp = fopen (KNOCKER_LOG_FILE, "a");
  else
    knocker_log_fp = fopen (filename, "a");

  if (knocker_log_fp == NULL)
    return -1;

  time (&timenow);
  knocker_time = ctime (&timenow);

  fprintf (knocker_log_fp, "%s", knocker_log_header);


  if (knocker_user.name != NULL)
    fprintf (knocker_log_fp, " - %s started by user %s on %s\n", PACKAGE, knocker_user.name, knocker_time);
  else
    fprintf (knocker_log_fp, " - %s started on %s\n", PACKAGE, knocker_time);

  /* fprintf(knocker_log_fp, "\n"); */

  fflush (knocker_log_fp);

  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_host_info (char *hostname_str, char *hostip_str)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, " - hostname to scan: %s\n", hostname_str);
  fprintf (knocker_log_fp, " - resolved host ip: %s\n", hostip_str);

  fflush (knocker_log_fp);
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_log_resolve_error (char *hostname_str)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, " - ERROR: failed to resolve hostname: %s\n", hostname_str);
  fprintf (knocker_log_fp, " - Aborting.\n");
  fprintf (knocker_log_fp, "\n\n");

  fclose (knocker_log_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_ports_info (int sp, int ep)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, " - - scan from port: %d\n", sp);
  fprintf (knocker_log_fp, " - - - scan to port: %d\n", ep);
  fprintf (knocker_log_fp, " - - - -  scan type: tcp connect\n");
  fprintf (knocker_log_fp, "+=- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  s c a n n i n g  -\n");
  fprintf (knocker_log_fp, "\n");

  fflush (knocker_log_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_open_port (int port, char *service_str)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, " -=[ %d/tcp, %s ]=- * OPEN *\n", port, service_str);
  fflush (knocker_log_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_results (char *hostname_str, char *hostip_str, int tot_ps, int open_ps, char *secs)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, "\n");
  fprintf (knocker_log_fp, "+=- - - - - - - - - - - - - - - - - - - - - - - - - - - -  c o m p l e t e d  -\n\n");
  fprintf (knocker_log_fp, " - scanned host name: %s ", hostname_str);
  fprintf (knocker_log_fp, "IP: %s\n\n", hostip_str);
  fprintf (knocker_log_fp, " - found %d open ports in a totoal of %d ports scanned.\n\n", open_ps, tot_ps);
  fprintf (knocker_log_fp, " - port scan completed in %s seconds.\n\n", secs);

  fflush (knocker_log_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_cancelled (void)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  fprintf (knocker_log_fp, "- * port scan cancelled by user * -\n");
  fflush (knocker_log_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_log_close (void)
{
  /* if logging to file is FALSE */
  if (knocker_args.logfile == FALSE)
    return;

  /* If a previous knocker_log_open () function call
     failed, we must not write to the file, since it hasn't been open
   */
  if (knocker_log_fp == NULL)
    return;

  fprintf (knocker_log_fp, "- -- - - - = http://knocker.sourceforge.net - bugs to - <g.gabriele79@genie.it>\n");
  fprintf (knocker_log_fp, "\n\n\n\n");
  fclose (knocker_log_fp);

}
