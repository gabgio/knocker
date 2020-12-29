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

#ifndef _KNOCKER_ARGS_H_
#define _KNOCKER_ARGS_H_

/* COMMAND LINE ARGUMENTS DEFINITION  */
/* ********************************** */
  /* host to scan */
#define HOST_SHORT_OPT "-H"
#define HOST_LONG_OPT  "--host"

  /* host to scan, got with lasthost  */
#define LAST_HOST_LONG_OPT  "--last-host"

  /* single port number */
#define SINGLE_PORT_SHORT_OPT "-P"
#define SINGLE_PORT_LONG_OPT  "--port"

  /* port number to start with */
#define START_PORT_SHORT_OPT "-SP"
#define START_PORT_LONG_OPT  "--start-port"

  /* port number to scan to */
#define END_PORT_SHORT_OPT "-EP"
#define END_PORT_LONG_OPT  "--end-port"

  /* Log scan results to file */
#define ENABLE_LOGFILE_SHORT_OPT "-lf"
#define ENABLE_LOGFILE_LONG_OPT  "--logfile"

  /* disable output to stdout, disable threads */
#define QUIET_MODE_SHORT_OPT "-q"
#define QUIET_MODE_LONG_OPT "--quiet"

  /* option to disable fency cool out put */
#define NO_FENCY_SHORT_OPT "-nf"
#define NO_FENCY_LONG_OPT  "--no-fency"

  /* option to disable colored out put */
#define NO_COLORS_SHORT_OPT "-nc"
#define NO_COLORS_LONG_OPT  "--no-colors"

 /* option --last-scan, reperforms the last port scan */
#define LAST_SCAN_LONG_OPT "--last-scan"

 /* option --configure, let the usere configure knocker */
#define CONFIGURE_LONG_OPT "--configure"

#define WIN32_FRONTEND_SHORT_OPT "--win32-frontend"
#define WIN32_FRONTEND_LONG_OPT "--win32-frontend"

#define HELP_SHORT_OPT    "-h"
#define HELP_LONG_OPT     "--help"

#define VERSION_SHORT_OPT "-v"
#define VERSION_LONG_OPT  "--version"
/* ********************************** */


typedef struct {
  char           *hname;      /* hostname string */
  char           *hip;        /* host IP string  */
  char           *lfname;     /* logfile name */
  unsigned int   port;        /* Single port number, -P */
  unsigned int   sport;       /* Start port number, -SP */
  unsigned int   eport;       /* End port number, -EP   */
  int logfile;     /* log to file TRUE,FALSE */
  int quiet;       /* quiet mode TRUE,FALSE  */
  int colors;      /* no colors, TRUE,FALSE  */
  int fency;       /* fency output, TRUE, FALSE */
  int win32_frontend;
} knocker_args_t;


extern knocker_args_t knocker_args; /* command line arguments structure */

/*
 Initialize a knocker_args_t type of structure
*/
int  knocker_args_init  (knocker_args_t *args, int logfile, int quiet, int colors);

/*
 Free a previously initialized knocker_args_t type of strucutre
*/
void knocker_args_free  (knocker_args_t *args);

/*
 Parse passed arguments, fills a previously initialized knocker_args_t type
 of structure, and hanndles some options like --version, and --help.
*/
int  knocker_args_parse (knocker_args_t *args, int argc, char *argv[]);

/*
 This tells knocker (returning TRUE or FALSE) if an option is enabled or not.
*/
/* int  knocker_args_argument (knocker_args_t *args, unsigned short argument); */

#endif /* _KNOCKER_ARGS_H_ */


