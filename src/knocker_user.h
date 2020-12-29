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

#ifndef _KNOCKER_USER_H_
#define _KNOCKER_USER_H_

typedef struct {
  char  *name;   /* user name  */
  char  *dir;    /* knocker dir under the user home ex: /home/user/.knocker */
  int    super;  /* user is root or not */
} knocker_user_t;

extern knocker_user_t knocker_user;

int   knocker_user_is_root ( void );
char *knocker_user_get_username ( void );
char *knocker_user_get_userhome ( void );

int  knocker_user_init (knocker_user_t *user);
void knocker_user_free (knocker_user_t *user);

int knocker_user_read_lastscan  (knocker_user_t *user, knocker_args_t *args);
int knocker_user_write_lastscan (knocker_user_t *user, knocker_args_t *args);

int knocker_user_read_lasthost (knocker_user_t *user, knocker_args_t *args);

#endif /* _KNOCKER_USER_H_ */
