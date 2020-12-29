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

#ifndef _KNOCKER_CONF_H_
#define _KNOCKER_CONF_H_

#define KNOCKER_CONFIG_FILE "knocker.conf"
#define KNOCKER_CONF_MAX_LEN 255  /* max line lenght in the conf file  */
#define KNOCKER_COMMENT_CHAR '#'  /* conf file comment char            */
#define KNOCKER_OPTION_TOKEN '='  /* conf file option/value separetor */ 

/* Default color definition for knocker */
#define KNOCKER_DEFAULT_COLOR_1  COLOR_GREEN
#define KNOCKER_DEFAULT_COLOR_2  COLOR_WHITE
#define KNOCKER_DEFAULT_COLOR_1_ATTR  ATTRIB_RESET
#define KNOCKER_DEFAULT_COLOR_2_ATTR  ATTRIB_BRIGHT

/* Options found in the config file */
#define KNOCKER_CONF_OPT_USE_COLORS    "USE_COLORS"
#define KNOCKER_CONF_OPT_COLOR_1       "COLOR_1" 
#define KNOCKER_CONF_OPT_COLOR_2       "COLOR_2"
#define KNOCKER_CONF_OPT_COLOR_1_ATTR  "COLOR_1_ATTR" 
#define KNOCKER_CONF_OPT_COLOR_2_ATTR  "COLOR_2_ATTR"


/* The actual values variable */
/* these values are read from the conf file */
/* by the knocker_conf_parse function */
extern int KNOCKER_USER_COLOR;
extern int KNOCKER_COLOR_1;
extern int KNOCKER_COLOR_2;
extern int KNOCKER_COLOR_1_ATTR;
extern int KNOCKER_COLOR_2_ATTR;

void knocker_conf_configure ( void );
int knocker_conf_parse ( void );
int knocker_conf_write_default ( void ); 

#endif /* _KNOCKER_CONF_H_ */
