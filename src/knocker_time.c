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

#include <stdio.h>
#include <stdlib.h>

#include "knocker_time.h"

#ifdef __WIN32__
#include <windows.h>
#else
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#endif /* __WIN32__ */

#ifdef __WIN32__
static unsigned long timer_start;
#else
static struct timeval timer_start;
#endif


void knocker_time_start_timer (void)
{
#ifdef __WIN32__
  timer_start = GetTickCount ();
#else
  /* Set first ticks value */
  gettimeofday (&timer_start, NULL);
#endif
}

double knocker_time_get_ticks (void)
{
  double ticks;
#ifdef __WIN32__
  double timer_now;
  na timer_now = GetTickCount ();
  ticks = ((timer_now - timer_start));

#else
  struct timeval timer_now;

  gettimeofday (&timer_now, NULL);
  ticks = (timer_now.tv_sec - timer_start.tv_sec) * 1000 + (timer_now.tv_usec - timer_start.tv_usec) / 1000;
#endif
  return (ticks);
}


void knocker_time_delay (unsigned long ms)
{
    double before;
    double now;

#ifdef __WIN32__

#else


/* #if defined (HAVE_PAUSE) && defined (HAVE_NANOSLEEP) */

/*   
# ifdef HAVE_NANOSLEEP
 --------------------- UNTESTED !!!!!!! -------------------------- 

        struct timespec rqtp;
        unsigned long pause;

        pause = pause;

        rqtp.tv_sec = (time_t) pause / 1000;

        rqtp.tv_nsec = (long) (pause % 1000) * 1000000;

        (void) nanosleep  (&rqtp, NULL);
*/

#ifdef HAVE_USLEEP


#else
  before = knocker_time_get_ticks ();
  now = before;

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_time_delay() called.\n");
  fprintf (stderr, "debug: timer is now = %f (it should be 0)\n", now);
  fprintf (stderr, "debug: delaying for %f milliseconds...", ms);
#endif

  /* Very bad do nothing delay loop */
  do
    {
      now = knocker_time_get_ticks ();

      if (now > before + ms)
        break;                  /* just to make sure we don't get stuck in this loop */
      /* if the test now <= before + ms fails        */

    }
  while (now <= before + ms);

#endif


#ifdef DEBUG
  fprintf (stderr, " done.\n");
  fprintf (stderr, "debug: timer is now = %f \n", now);
#endif

#endif /* ifdef __WIN32__ */
}
