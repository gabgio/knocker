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

#ifndef _KNOCKER_OUTPUT_H_
#define _KNOCKER_OUTPUT_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KNOCKER_OUTPUT_FP stdout
#define knocker_output_fp KNOCKER_OUTPUT_FP

int  knocker_output_open ( void );
void knocker_output_host_info (const char *hostname_str, const char *hostip_str);
void knocker_output_resolve_error (char *hostname_str);
void knocker_output_ports_info (int sp, int ep);
void knocker_output_open_port (int port, char *service_str);
void knocker_output_results (char *hostname_str, char *hostname_ip, int tot_ps, int open_ps,char *secs);

#endif /* _KNOCKER_OUTPUT_H_ */
