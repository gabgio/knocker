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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knocker_led.h"

#ifdef __WIN32__

#elif defined NO_LED

#else 

#include <fcntl.h>
#include <linux/kd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#endif /* __WIN32__ */



/* Led values are in the linux/kd.h include */
#define LED_VALUE_NUM   LED_NUM
#define LED_VALUE_CAP   LED_CAP
#define LED_VALUE_SCR   LED_SCR


#ifndef NO_LED
static int initialized = 0;
#endif

/*
   ============================================================================
   ============================================================================
*/
static int knocker_led_init (knocker_led_t * knocker_leds)
{
#ifndef NO_LED
  ioctl (0, KDSETLED, 0xff);

  knocker_leds->num = 0;
  knocker_leds->caps = 0;
  knocker_leds->scroll = 0;

  knocker_leds->sequence = 0;

  initialized = 1; 
#endif
  return 0;
}

/*
   ============================================================================
   ============================================================================
*/
static void knocker_led_quit (knocker_led_t * knocker_leds)
{
#ifndef NO_LED
  if (!initialized)
    return;

  knocker_leds->num = 0;
  knocker_leds->caps = 0;
  knocker_leds->scroll = 0;

  knocker_leds->sequence = 0;

  initialized = 0;
#endif
  return;
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_led_turn_on (int led)
{
#ifndef NO_LED
  char state;

  if (!initialized)
    knocker_led_init (&knocker_led_status);

  ioctl (0, KDGETLED, &state);

  if (led == KNOCKER_LED_NUMLOCK)
    {
      if (!knocker_led_status.num)
        {
          ioctl (0, KDSETLED, LED_VALUE_NUM);
          knocker_led_status.num = 1;
        }
    }
  else if (led == KNOCKER_LED_CAPSLOCK)
    {
      if (!knocker_led_status.caps)
        {
          ioctl (0, KDSETLED, LED_VALUE_CAP);
          knocker_led_status.caps = 1;
        }
    }
  else if (led == KNOCKER_LED_SCROLLOCK)
    {
      if (!knocker_led_status.scroll)
        {
          ioctl (0, KDSETLED, LED_VALUE_SCR);
          knocker_led_status.scroll = 1;
        }
    }  
#endif
  return;
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_led_turn_off (int led)
{
#ifndef NO_LED
  char state;

  if (!initialized)
    return;

  ioctl (0, KDGETLED, &state);

  if (led == KNOCKER_LED_NUMLOCK)
    {
      if (knocker_led_status.num)
        {
          ioctl (0, KDSETLED, state & ~LED_VALUE_NUM);
          /*ioctl (0, KDSETLED, 0xff); */
          knocker_led_status.num = 0;
        }
    }
  else if (led == KNOCKER_LED_CAPSLOCK)
    {
      if (knocker_led_status.caps)
        {
          ioctl (0, KDSETLED, state & ~LED_VALUE_CAP);
          /* ioctl (0, KDSETLED, 0xff); */
          knocker_led_status.caps = 0;
        }
    }
  else if (led == KNOCKER_LED_SCROLLOCK)
    {
      if (knocker_led_status.scroll)
        {
          ioctl (0, KDSETLED, state & ~LED_VALUE_SCR);
          /* ioctl (0, KDSETLED, 0xff); */
          knocker_led_status.scroll = 0;
        }
    }
#endif

 return;
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_led_turn_on_all (void)
{
#ifndef NO_LED


  if (!initialized)
    knocker_led_init (&knocker_led_status);

  ioctl (0, KDSETLED, LED_VALUE_SCR | LED_VALUE_NUM | LED_VALUE_CAP);

  knocker_led_status.num = 1;
  knocker_led_status.caps = 1;
  knocker_led_status.scroll = 1;
#endif
  return;
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_led_turn_off_all (void)
{
#ifndef NO_LED
  char state;

  if (!initialized)
    return;

  ioctl (0, KDGETLED, &state);
  ioctl (0, KDSETLED, state & ~(LED_VALUE_SCR | LED_VALUE_NUM | LED_VALUE_CAP));

  knocker_led_status.num = 0;
  knocker_led_status.caps = 0;
  knocker_led_status.scroll = 0;
#endif
 return;
}


/*
   ============================================================================
   ============================================================================
*/
void knocker_led_sequence (void)
{
#ifndef NO_LED

  if (ledt > led_delay)
    ledt = 0;

  if (ledt < 0)
    ledt = 0;

  ledt++;

  if (ledt != led_delay)
    return;

  if (knocker_led_status.sequence == 0)
    {
      /* no leds were on before */
      /* turn on the first one */
      knocker_led_turn_on (KNOCKER_LED_NUMLOCK);
      knocker_led_status.sequence = 1;
      return;
    }
  else if (knocker_led_status.sequence == 1)
    {
      /* NumLock was on before */
      /* turn it off */

      knocker_led_turn_off (KNOCKER_LED_NUMLOCK);

      knocker_led_turn_on (KNOCKER_LED_CAPSLOCK);

      knocker_led_status.sequence = 2;
      return;
    }
  else if (knocker_led_status.sequence == 2)
    {
      /* CapsLock was on before */
      /* turn it off */
      knocker_led_turn_off (KNOCKER_LED_CAPSLOCK);

      knocker_led_turn_on (KNOCKER_LED_SCROLLOCK);

      knocker_led_status.sequence = 3;
      return;
    }
  else if (knocker_led_status.sequence == 3)
    {
      /* ScrolLock was on before */
      /* turn it off */
      knocker_led_turn_off (KNOCKER_LED_SCROLLOCK);

      knocker_led_turn_on (KNOCKER_LED_NUMLOCK);

      knocker_led_status.sequence = 1;
      return;
    }
#endif
 return;
}

/*
   ============================================================================
   ============================================================================
*/
void knocker_led_reset (void)
{

#ifndef NO_LED

  if (initialized)
    knocker_led_quit (&knocker_led_status);

  ioctl (0, KDSETLED, 0xff);
#endif
 return;
}
