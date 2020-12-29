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

#ifndef _KNOCKER_TERM_H_
#define _KNOCKER_TERM_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>

#ifdef __WIN32__
#include <conio.h>
#define COLOR_BLACK       BLACK
#define COLOR_BLUE        BLUE
#define COLOR_GREEN       GREEN
#define COLOR_CYAN        CYAN
#define COLOR_RED         RED
#define COLOR_MAGENTA     MAGENTA
#define COLOR_WHITE       WHITE
#define COLOR_YELLOW      YELLOW
#else
enum
{
  COLOR_BLACK, COLOR_RED, COLOR_GREEN,
  COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA,
  COLOR_CYAN, COLOR_WHITE
};
#endif /* __WIN_32__ */

#define COLOR_NONE        -2002 /* just to be sure it doesn't conflict with other colors */

enum
{
  ATTRIB_RESET, ATTRIB_BRIGHT, ATTRIB_DIM, ATTRIB_UNDERLINE,
  ATTRIB_BLINK, ATTRIB_REVERSE, ATTRIB_HIDDEN
};


void knocker_term_clear ( void );

void knocker_term_set_color (int fg, int bg, int attrib);
void knocker_term_set_default_color (void);
void knocker_term_reset (void);

void knocker_term_fflush (FILE *fd);

void knocker_term_printf (const char *buffer);
void knocker_term_fprintf (FILE * fd, const char *buffer);
void knocker_term_intfprintf (FILE * fd, const int i);

void knocker_term_color_printf (const char *buffer, int color, int attrib);
void knocker_term_color_fprintf (FILE * fd, const char *buffer, int color, int attrib);

void knocker_term_color_intprintf (const int i, int color, int attrib);
void knocker_term_color_intfprintf (FILE * fd, const int i, int color, int attrib);

#endif /* _KNOCKER_TERM_H_ */

