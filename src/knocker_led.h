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

#ifndef _KNOCKER_LED_H_
#define _KNOCKER_LED_H_


#ifdef HAVE_CONFIG_H
#include <config.h>

/* If we have config.h and NO_LED has not been defined  */
/* we check for the include needed by the led functions */
/* if a include is missing, led are disabled.           */

#ifndef NO_LED

#ifndef HAVE_FCNTL_H
#define NO_LED
#endif

#ifndef HAVE_SYS_IOCTL_H
#define NO_LED
#endif

#ifndef HAVE_LINUX_KD_H
#define NO_LED
#endif

#endif /* ifndef NO_LED */
#endif /* ifdef HAVE_CONFIG_H */


#ifdef        __WIN32__
/* no led yet under WIN32 */
#define NO_LED
#endif


enum { KNOCKER_LED_NUMLOCK, KNOCKER_LED_CAPSLOCK, KNOCKER_LED_SCROLLOCK };

typedef struct {
  int num;
  int caps;
  int scroll;
  int sequence;  /* used in knocker_led_sequence() only */
} knocker_led_t;

knocker_led_t knocker_led_status;

void knocker_led_turn_on  (int led);
void knocker_led_turn_off (int led);
void knocker_led_turn_on_all ( void );
void knocker_led_turn_off_all ( void );
void knocker_led_sequence ( void );
void knocker_led_reset ( void );

#define led_delay 1
int ledt;

#endif /* _KNOCKER_LED_H_ */


