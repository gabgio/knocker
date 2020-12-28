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
#include "knocker_output.h"
#include "knocker_conf.h"
#include "knocker_args.h"
#include "knocker_term.h"
#include "knocker_user.h"
#include "knocker_time.h"

const char knocker_header[12][90] = {
  "+-----------------------------------------------------------------------------+\n",
  "|--=|", " k n o c k e r ", "--", " t h e ", "--", " n e t ", "--",
  " p o r t s c a n n e r ", "|=-=[ ", VERSION, " ]=-|\n"
};


char *knocker_time;

/*
   ============================================================================
   ============================================================================
*/
int knocker_output_open (void)
{
  time_t timenow;

  if (!knocker_args.fency)
    return 0;



  time (&timenow);
  knocker_time = ctime (&timenow);

  knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);

  /* print the colored header */
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[0], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[1], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[2], KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[3], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[4], KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[5], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[6], KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[7], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[8], KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[9], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[10], KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[11], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, knocker_header[0], KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);


  if (knocker_user.name != NULL)
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "started by user ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, knocker_user.name, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " on ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, knocker_time, KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  else
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "started on ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, knocker_time, KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }

  fflush (knocker_output_fp);

  return 0;
}



/*
   ============================================================================
   ============================================================================
*/
void knocker_output_host_info (const char *hostname_str, const char *hostip_str)
{
  if (knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, " - ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "hostname to scan: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);

      knocker_term_color_fprintf (knocker_output_fp, " - ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "resolved host ip: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostip_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  else
    {
      knocker_term_color_fprintf (knocker_output_fp, "Host: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " resolved: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostip_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  fflush (knocker_output_fp);
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_output_resolve_error (char *hostname_str)
{
  if (knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, " - ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "failed to resolve given hostname/IP: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - Aborting\n\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  else
    {
      knocker_term_color_fprintf (knocker_output_fp, "Failed to resolve hostname/IP: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  fflush (knocker_output_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_output_ports_info (int sp, int ep)
{
  if (!knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      return;
    }
  knocker_term_color_fprintf (knocker_output_fp, " - - scan from port: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_intfprintf (knocker_output_fp, sp, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n - - - scan to port: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_intfprintf (knocker_output_fp, ep, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n - - - -  scan type: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "tcp connect", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n\n+=- - - - - - - - - - - - - - - - - - - - - - - - - - - - - ",
                              KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, " s c a n n i n g ", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, " -\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
  knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);

  fflush (knocker_output_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_output_open_port (int port, char *service_str)
{
  if (knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, " -=[ ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_intfprintf (knocker_output_fp, port, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "/", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "tcp", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, ", ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, service_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " ]=-", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " * ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "OPEN", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " *\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  else
    {
      knocker_term_color_intfprintf (knocker_output_fp, port, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "/", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "tcp", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, ", ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, service_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, ", ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "open", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  fflush (knocker_output_fp);
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_output_results (char *hostname_str, char *hostname_ip, int tot_ps,  int open_ps, char *secs)
{
  if (knocker_args.fency)
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "+=- - - - - - - - - - - - - - - - - - - - - - - - - - - - ",
                                  KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " c o m p l e t e d ", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " -\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - scanned host name: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_str, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " IP: ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, hostname_ip, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);

      knocker_term_color_fprintf (knocker_output_fp, "\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - found ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_intfprintf (knocker_output_fp, open_ps, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " open ports in a total of ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_intfprintf (knocker_output_fp, tot_ps, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " ports scanned.\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " - port scan completed in ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, secs, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " seconds.\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }
  else
    {
      knocker_term_color_fprintf (knocker_output_fp, "\n", KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, "Found ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_intfprintf (knocker_output_fp, open_ps, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " open ports in a total of ", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_intfprintf (knocker_output_fp, tot_ps, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " ports scanned (", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, secs, KNOCKER_COLOR_2, KNOCKER_COLOR_2_ATTR);
      knocker_term_color_fprintf (knocker_output_fp, " secs).\n\n", KNOCKER_COLOR_1, KNOCKER_COLOR_1_ATTR);
    }

  fflush (knocker_output_fp);
}
