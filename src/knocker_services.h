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

#ifndef _KNOCKER_SERVICES_H_
#define _KNOCKER_SERVICES_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define SERVICES_DB_TOTAL_SERVICES 30000 /* was erroneously 231 */ 

extern int knocker_core_services_db_init;

extern char *knocker_core_services_db[SERVICES_DB_TOTAL_SERVICES];

int  init_knocker_core_services_db ( void );
void free_knocker_core_services_db ( void );

char *knocker_core_services_db_get_service  (unsigned int port, int protocol);

#endif /* _KNOCKER_SERVICES_H_ */





