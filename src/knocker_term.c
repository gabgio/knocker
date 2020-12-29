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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


#include <stdlib.h>
#include <string.h>

#include "knocker_core.h"
#include "knocker_term.h"
#include "knocker_args.h"


void knocker_term_clear (void)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_term_clear (...) called\n");
#endif

  if (knocker_args.quiet == FALSE)
    {
#ifdef DEBUG
  fprintf (stderr, "debug: quiet mode is enabled\n");
#endif

#ifdef __WIN32__
      clrscr ();                /* clear the screen using clrscr() from conio.h */
#else
      system ("clear");         /* this should work on the most of the UNIX and UNIX-like */
#endif /* __WIN32__ */
    }
}

void knocker_term_set_default_color (void)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_term_set_default_color (...) called\n");
#endif

  if (!knocker_args.quiet)
    {
      if (knocker_args.colors == TRUE)
        {
#ifdef DEBUG
  fprintf (stderr, "debug: colors enabled\n");
#endif

#ifdef __WIN32__
          /* in win32 the default fg color is LIGHTGRAY */
          knocker_term_set_color (LIGHTGRAY, COLOR_NONE, ATTRIB_RESET);
#else
          knocker_term_set_color (COLOR_WHITE, COLOR_NONE, ATTRIB_RESET);
#endif
        }

    }

  return;
}


void knocker_term_reset (void)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_term_reset (...) called\n");
#endif

  knocker_term_set_default_color ();

  /* Something must be printed to actually reset the terminal to the defaults */

#ifdef __WIN32__
  /* in win32 the default fg color is LIGHTGRAY */
  /* cprintf ( " " ); */
#else
  /* fprintf ( stdout, " " );  */
#endif


  return;
}


void knocker_term_set_color (int fg, int bg, int attrib)
{
  if (knocker_args.quiet == FALSE)
    {
      char cmd_str[13];

      if (knocker_args.colors == TRUE)
        {
          if ((bg == COLOR_NONE) && (fg != COLOR_NONE))
            {
#ifdef __WIN32__
              textcolor (fg);
#else
              /* this one doesn't change the background current color */
              sprintf (cmd_str, "%c[%d;%dm", 0x1B, attrib, fg + 30);
#endif
            }
          else if ((bg != COLOR_NONE) && (fg == COLOR_NONE))
            {
#ifdef __WIN32__
              textbackground (bg);
#else
              /* this one doesn't change the foreground current color */
              sprintf (cmd_str, "%c[%d;%dm", 0x1B, attrib, bg + 40);
#endif
            }
          else if ((bg == COLOR_NONE) && (fg == COLOR_NONE))
            {
#ifndef __WIN32__
              /* this one doesn't change the background color and the foreground color neither */
              sprintf (cmd_str, "%c[%dm", 0x1B, attrib);
#endif
            }
          else
            {
#ifdef __WIN32__
              textcolor (fg);
              textbackground (bg);
#else
              sprintf (cmd_str, "%c[%d;%d;%dm", 0x1B, attrib, fg + 30, bg + 40);
#endif
            }
          fprintf (stdout, "%s", cmd_str);

        }
    }

  return;
}


void knocker_term_fflush (FILE * fd)
{
  if (knocker_args.quiet == FALSE)
    {
      fflush (fd);
    }
}


void knocker_term_printf (const char *buffer)
{
  if (knocker_args.quiet == FALSE)
    {
      printf ("%s", buffer);

    }

  return;
}


void knocker_term_fprintf (FILE * fd, const char *buffer)
{
  if (knocker_args.quiet == FALSE)
    {
      fprintf (fd, "%s", buffer);
    }

  return;
}


void knocker_term_color_printf (const char *buffer, int color, int attrib)
{
  if (knocker_args.quiet == FALSE)
    {
      knocker_term_set_color (color, COLOR_NONE, attrib);
#ifdef __WIN32__
      cprintf ("%s", buffer);
#else
      printf ("%s", buffer);
#endif
      knocker_term_set_default_color ();
    }

  return;
}


void knocker_term_color_fprintf (FILE * fd, const char *buffer, int color, int attrib)
{
  if (knocker_args.quiet == FALSE)
    {
      knocker_term_set_color (color, COLOR_NONE, attrib);
#ifdef __WIN32__
      cprintf ("%s", buffer);
#else
      fprintf (fd, "%s", buffer);
#endif
      knocker_term_set_default_color ();
    }

  return;
}


void knocker_term_color_intprintf (const int i, int color, int attrib)
{
  if (knocker_args.quiet == FALSE)
    {
      knocker_term_set_color (color, COLOR_NONE, attrib);
#ifdef __WIN32__
      cprintf ("%d", i);
#else
      printf ("%d", i);
#endif
      knocker_term_set_default_color ();
    }

  return;
}

void knocker_term_color_intfprintf (FILE * fd, const int i, int color, int attrib)
{
  if (knocker_args.quiet == FALSE)
    {
      knocker_term_set_color (color, COLOR_NONE, attrib);
#ifdef __WIN32__
      cprintf ("%d", i);
#else
      fprintf (fd, "%d", i);
#endif
      knocker_term_set_default_color ();
    }

  return;
}

void knocker_term_intfprintf (FILE * fd, const int i)
{
  if (knocker_args.quiet == FALSE)
    {
#ifdef __WIN32__
      cprintf ("%d", i);
#else
      fprintf (fd, "%d", i);
#endif
    }

  return;
}

/*
 * function: restore_terminal - restore normal screen mode.
 * algorithm: uses the 'stty' command to restore normal screen mode.
 *            serves as a cleanup function for the user input thread.
 * input: none.
 * output: none.
 */
/*
void restore_terminal (void)
{
    restore_terminal: before 'stty -raw echo'

  system ("stty -raw echo");

   restore_terminal: after 'stty -raw echo'

}
*/
