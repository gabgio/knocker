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

#ifndef _KNOCKER_LOG_H_
#define _KNOCKER_LOG_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KNOCKER_LOG_FILE "knocker_scan.log"
FILE *knocker_log_fp;

int  knocker_log_open (const char *filename);
void knocker_log_host_info (char *hostname_str, char *hostip_str);
void knocker_log_resolve_error (char *hostname_str);
void knocker_log_ports_info (int sp, int ep);
void knocker_log_open_port (int port, char *service_str);
void knocker_log_results (char *hostname_str, char *hostip_str, int tot_ps, int open_ps, char *secs);
void knocker_log_cancelled (void);
void knocker_log_close (void);

#endif /* _KNOCKER_LOG_H_ */

