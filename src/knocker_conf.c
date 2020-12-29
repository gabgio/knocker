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
#include <string.h>

#include "knocker_core.h"
#include "knocker_args.h"
#include "knocker_term.h"
#include "knocker_user.h"
#include "knocker_conf.h"


static int _isblank (int c)
{
  if (c == '\t')
    return 0;

  if (c == ' ')
    return 0;

  return 1;
}


static int _isno (char *answer)
{
  if (!strcmp (answer, "N"))
    return 1;

  else if (!strcmp (answer, "NO"))
    return 1;

  else if (!strcmp (answer, "n"))
    return 1;

  else if (!strcmp (answer, "no"))
    return 1;

  return 0;
}


static int _isyes (char *answer)
{


  if (!strcmp (answer, "Y"))
    {

      return 1;
    }
  else if (!strcmp (answer, "YES"))
    {

      return 1;
    }
  else if (!strcmp (answer, "y"))
    {

      return 1;
    }
  else if (!strcmp (answer, "yes"))
    {

      return 1;
    }
  else
    return 0;

  return 0;
}


static char *_get_answer (char *answer)
{
  char *tmp = malloc (KNOCKER_CONF_MAX_LEN);

  /* Looks like I have problems using fgets */
  /*
     if ( fgets(tmp, KNOCKER_CONF_MAX_LEN, stdin) == NULL)
     {
     free(tmp);
     return NULL;
     } 
   */
/* Let's go for the good old scanf */

  fscanf (stdin, "%s", tmp);

  if (answer == NULL)
    answer = malloc (strlen (tmp) + 1);
  else
    answer = realloc (answer, strlen (tmp) + 1);

  strcpy (answer, tmp);
  free (tmp);

  return answer;
}


static int _iscommented (char *line, char comment)
{
  int first_char = 0;
  int i = 0;

  if (line[0] == comment)
    return 1;

  while (i < strlen (line))
    {
      if (line[i] == '\0')
        return 0;

      if (_isblank (line[i]) && !first_char)
        i++;

      if (line[i] != comment && !first_char)
        return 0;

      if ((line[i] == comment) && !first_char)
        return 1;

      else if ((line[i] != comment) && !first_char)
        return 0;

      i++;
    }

  return 0;
}


static int _isvalid (char *line, char token)
{
  /* Check for the  KNOCKER_OPTION_TOKEN  char */
  if (strchr (line, token) == NULL)
    return 0;

  return 1;
}


static int _fgetline (FILE * fp, char *line, int maxlen)
{
  int i = 0;
  int c;

  while (i < maxlen)
    {
      c = fgetc (fp);

      if (c == EOF)
        {
          line[i] = '\0';
          return (EOF);
        }

      if (c == '\n')
        break;

      line[i] = c;

      i++;
    }

  line[i] = '\0';

  return (i);
}


static int _getoptval (char *line, char *opt, char *value)
{
  char *tmpp = malloc (strlen (line));
  char *p = malloc (strlen (line));

  /* Check if the option is present in the line */
  tmpp = strstr (line, opt);

  if (tmpp == NULL)
    return 0;                   /* nope */

  tmpp = tmpp + strlen (opt);

  if (!_isblank (*tmpp) || *tmpp != KNOCKER_OPTION_TOKEN)
    {
      /* free(tmpp); this cause knocker to segfault */
      return 0;
    }

  /* Check for the  KNOCKER_OPTION_TOKEN  char */
  p = strchr (line, KNOCKER_OPTION_TOKEN);

  p++;

  value = realloc (value, strlen (p) + 1);

  strcpy (value, p);

  /* free(p); this cause knocker to segfault */
  /* well I have to know why... */

  return 1;
}


int _get_color_by_opt (char *opt_value)
{
  int color;

  if (!strcmp (opt_value, "black"))
    color = COLOR_BLACK;
  else if (!strcmp (opt_value, "red"))
    color = COLOR_RED;
  else if (!strcmp (opt_value, "green"))
    color = COLOR_GREEN;
  else if (!strcmp (opt_value, "yellow"))
    color = COLOR_YELLOW;
  else if (!strcmp (opt_value, "blue"))
    color = COLOR_BLUE;
  else if (!strcmp (opt_value, "magenta"))
    color = COLOR_MAGENTA;
  else if (!strcmp (opt_value, "cyan"))
    color = COLOR_CYAN;
  else if (!strcmp (opt_value, "white"))
    color = COLOR_WHITE;
  else
    color = -1;                 /* not a valid color */

  return color;
}

int _get_color_attrib_by_opt (char *opt_value)
{
  int attrib;

  if (!strcmp (opt_value, "normal"))
    attrib = ATTRIB_RESET;
  else if (!strcmp (opt_value, "bright"))
    attrib = ATTRIB_BRIGHT;
  else if (!strcmp (opt_value, "underline"))
    attrib = ATTRIB_UNDERLINE;
  else if (!strcmp (opt_value, "blink"))
    attrib = ATTRIB_BLINK;
  else if (!strcmp (opt_value, "reverse"))
    attrib = ATTRIB_REVERSE;
  else
    attrib = -1;                /* not a valid attrib */

  return attrib;
}

void _set_color_conf (char *opt_value, int n, int attr)
{
  if ((n == 1) && (!attr))
    {
      /* KNOCKER_COLOR_1 */
      KNOCKER_COLOR_1 = _get_color_by_opt (opt_value);

      if (KNOCKER_COLOR_1 == -1)
        KNOCKER_COLOR_1 = KNOCKER_DEFAULT_COLOR_1;
    }
  else if ((n == 1) && (attr))
    {
      /* KNOCKER_COLOR_1_ATTR */
      KNOCKER_COLOR_1_ATTR = _get_color_attrib_by_opt (opt_value);

      if (KNOCKER_COLOR_1_ATTR == -1)
        KNOCKER_COLOR_1_ATTR = KNOCKER_DEFAULT_COLOR_1_ATTR;

    }
  else if ((n == 2) && (!attr))
    {
      /* KNOCKER_COLOR_2 */
      KNOCKER_COLOR_2 = _get_color_by_opt (opt_value);

      if (KNOCKER_COLOR_2 == -1)
        KNOCKER_COLOR_2 = KNOCKER_DEFAULT_COLOR_2;

    }
  else if ((n == 2) && (attr))
    {
      /* KNOCKER_COLOR_2_ATTR */
      KNOCKER_COLOR_2_ATTR = _get_color_attrib_by_opt (opt_value);

      if (KNOCKER_COLOR_2_ATTR == -1)
        KNOCKER_COLOR_2_ATTR = KNOCKER_DEFAULT_COLOR_2_ATTR;

    }
}

void knocker_conf_set_default (void)
{
  KNOCKER_COLOR_1 = KNOCKER_DEFAULT_COLOR_1;
  KNOCKER_COLOR_1_ATTR = KNOCKER_DEFAULT_COLOR_1_ATTR;
  KNOCKER_COLOR_2 = KNOCKER_DEFAULT_COLOR_2;
  KNOCKER_COLOR_2_ATTR = KNOCKER_DEFAULT_COLOR_2_ATTR;
}


int knocker_conf_parse (void)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_conf_parse() called.\n");
#endif
  FILE *fp;

  char *conf_file = NULL;
  char *linebuff = NULL;
  char *opt_value = NULL;

  conf_file = malloc (strlen (knocker_user.dir) + strlen ("/") + strlen (KNOCKER_CONFIG_FILE) + 1);

  strcpy (conf_file, knocker_user.dir);
  strcat (conf_file, "/");
  strcat (conf_file, KNOCKER_CONFIG_FILE);

#ifdef DEBUG
  fprintf (stderr, "debug: conf_file is %s.\n",conf_file);
#endif

  if ((fp = fopen (conf_file, "r")) == NULL)
    {
      /* fprintf (stderr, "couldn't read config file %s\n", conf_file); */
      free (conf_file);
      knocker_conf_set_default ();      /* run with the default configuration */
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_conf_parse() returns -1.\n");
#endif

      return -1;
    }

  linebuff = malloc (KNOCKER_CONF_MAX_LEN);
  opt_value = malloc (KNOCKER_CONF_MAX_LEN);

  while (!feof (fp))
    {
      if (_fgetline (fp, linebuff, KNOCKER_CONF_MAX_LEN) == EOF)
        {
          break;
        }

      if (!_iscommented (linebuff, KNOCKER_COMMENT_CHAR))
        {
          if (_isvalid (linebuff, KNOCKER_OPTION_TOKEN))
            {
              if (_getoptval (linebuff, KNOCKER_CONF_OPT_USE_COLORS, opt_value))
                {
                  if (_isno (opt_value))
                       knocker_args.colors = 0;
                  else if  (_isyes (opt_value))
                       knocker_args.colors = 1;
                  else 
                       knocker_args.colors = 1;  /* unless is a no colors are enabled */         
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_1, opt_value))
                {
                  _set_color_conf (opt_value, 1, 0);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_2, opt_value))
                {
                  _set_color_conf (opt_value, 2, 0);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_1_ATTR, opt_value))
                {
                  _set_color_conf (opt_value, 1, 1);
                }
              else if (_getoptval (linebuff, KNOCKER_CONF_OPT_COLOR_2_ATTR, opt_value))
                {
                  _set_color_conf (opt_value, 2, 1);
                }
            }
        }
    }                           /* end of while(!foef(fp)) */


  fclose (fp);

  if (conf_file != NULL)
    free (conf_file);
   if (linebuff != NULL)
    free (linebuff);
  if (opt_value != NULL)
    free (opt_value);

#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_conf_parse() returns 0.\n");
#endif

  return 0;
}

int knocker_conf_write_default (void)
{
  FILE *fp;

  char *conf_file = NULL;

  conf_file = malloc (strlen (knocker_user.dir) + strlen ("/") + strlen (KNOCKER_CONFIG_FILE) + 1);

  strcpy (conf_file, knocker_user.dir);
  strcat (conf_file, "/");
  strcat (conf_file, KNOCKER_CONFIG_FILE);

  if ((fp = fopen (conf_file, "w")) == NULL)
    {
      /* printf (stderr, "couldn't write config file %s\n", conf_file); */
      knocker_conf_set_default ();      /* run with the default configuration */
      free (conf_file);
      return -1;
    }

  fprintf (fp, "%c Config file for %s. Copyright (C) 2001-2002 %s\n", KNOCKER_COMMENT_CHAR, PACKAGE, _KNOCKER_CORE_AUTHOR_);
  fprintf (fp, "%c %s %s\n", KNOCKER_COMMENT_CHAR, _KNOCKER_CORE_AUTHOR_EMAIL_, _KNOCKER_CORE_HOMEPAGE_);
  fprintf (fp, "\n");
  fprintf (fp, "%c Edit as you need.\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "\n");
  fprintf (fp, "%c TO USE COLORS OR NOT TO USE COLORS ?\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c If you say no here, colors won't be used, otherwise yes\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%s%cyes\n", KNOCKER_CONF_OPT_USE_COLORS, KNOCKER_OPTION_TOKEN);
  fprintf (fp, "\n");
  fprintf (fp, "%c COLORS AND COLORS ATTRIBUTES:\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c These are for the %s colored output, you can choose what colors\n", KNOCKER_COMMENT_CHAR, PACKAGE);
  fprintf (fp, "%c are to be used.\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c Valid values for COLOR are:\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c black, red, green, yellow, blue, magenta, cyan, white.\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c Valid ATTRIBS are:\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c normal, bright, underline, blink, reverse\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%s%cgreen\n", KNOCKER_CONF_OPT_COLOR_1, KNOCKER_OPTION_TOKEN);
  fprintf (fp, "%s%cnormal\n", KNOCKER_CONF_OPT_COLOR_1_ATTR, KNOCKER_OPTION_TOKEN);
  fprintf (fp, "\n");
  fprintf (fp, "%s%cwhite\n", KNOCKER_CONF_OPT_COLOR_2, KNOCKER_OPTION_TOKEN);
  fprintf (fp, "%s%cbright\n", KNOCKER_CONF_OPT_COLOR_2_ATTR, KNOCKER_OPTION_TOKEN);
  fprintf (fp, "\n");

  free (conf_file);
  fclose (fp);

  return 0;
}

int knocker_conf_write (int use_colors, char *color1, char *color2, char *color1_attr, char *color2_attr)
{
  FILE *fp;

  char *conf_file = NULL;

  conf_file = malloc (strlen (knocker_user.dir) + strlen ("/") + strlen (KNOCKER_CONFIG_FILE) + 1);

  strcpy (conf_file, knocker_user.dir);
  strcat (conf_file, "/");
  strcat (conf_file, KNOCKER_CONFIG_FILE);

  if ((fp = fopen (conf_file, "w")) == NULL)
    {
      /* printf (stderr, "couldn't write config file %s\n", conf_file); */
      /* knocker_conf_set_default (); not needed here since this function is only called by --configure */
      /* we will just exit after that */
      fprintf (stderr, "\n%s: error, couldn't write configuration file: %s\n", PACKAGE, conf_file);
      free (conf_file);
      return -1;
    }

  fprintf (stdout, "\nWriting configuration file... ");

  fprintf (fp, "%c Config file for %s. Copyright (C) 2001-2002 %s\n", KNOCKER_COMMENT_CHAR, PACKAGE, _KNOCKER_CORE_AUTHOR_);
  fprintf (fp, "%c %s %s\n", KNOCKER_COMMENT_CHAR, _KNOCKER_CORE_AUTHOR_EMAIL_, _KNOCKER_CORE_HOMEPAGE_);
  fprintf (fp, "\n");
  fprintf (fp, "%c Edit as you need.\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "\n");
  fprintf (fp, "%c TO USE COLORS OR NOT TO USE COLORS ?\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c If you say no here, colors won't be used, otherwise yes\n", KNOCKER_COMMENT_CHAR);
  fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);

  if (use_colors)
    fprintf (fp, "%s%cyes\n", KNOCKER_CONF_OPT_USE_COLORS, KNOCKER_OPTION_TOKEN);
  else
    fprintf (fp, "%s%cno\n", KNOCKER_CONF_OPT_USE_COLORS, KNOCKER_OPTION_TOKEN);


  if (color1 != NULL && color2 != NULL && color1_attr != NULL && color2_attr != NULL)
    {

      fprintf (fp, "\n");
      fprintf (fp, "%c COLORS AND COLORS ATTRIBUTES:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c These are for the %s colored output, you can choose what colors\n", KNOCKER_COMMENT_CHAR, PACKAGE);
      fprintf (fp, "%c are to be used.\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c Valid values for COLOR are:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c black, red, green, yellow, blue, magenta, cyan, white.\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c Valid ATTRIBS are:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c normal, bright, underline, blink, reverse\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%s%c%s\n", KNOCKER_CONF_OPT_COLOR_1, KNOCKER_OPTION_TOKEN, color1);
      fprintf (fp, "%s%c%s\n", KNOCKER_CONF_OPT_COLOR_1_ATTR, KNOCKER_OPTION_TOKEN, color1_attr);
      fprintf (fp, "\n");
      fprintf (fp, "%s%c%s\n", KNOCKER_CONF_OPT_COLOR_2, KNOCKER_OPTION_TOKEN, color2);
      fprintf (fp, "%s%c%s\n", KNOCKER_CONF_OPT_COLOR_2_ATTR, KNOCKER_OPTION_TOKEN, color2_attr);
      fprintf (fp, "\n");

    }

  else
    {

      fprintf (fp, "\n");
      fprintf (fp, "%c COLORS AND COLORS ATTRIBUTES:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c These are for the %s colored output, you can choose what colors\n", KNOCKER_COMMENT_CHAR, PACKAGE);
      fprintf (fp, "%c are to be used.\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c Valid values for COLOR are:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c black, red, green, yellow, blue, magenta, cyan, white.\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c Valid ATTRIBS are:\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c normal, bright, underline, blink, reverse\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%c\n", KNOCKER_COMMENT_CHAR);
      fprintf (fp, "%s%cgreen\n", KNOCKER_CONF_OPT_COLOR_1, KNOCKER_OPTION_TOKEN);
      fprintf (fp, "%s%cnormal\n", KNOCKER_CONF_OPT_COLOR_1_ATTR, KNOCKER_OPTION_TOKEN);
      fprintf (fp, "\n");
      fprintf (fp, "%s%cwhite\n", KNOCKER_CONF_OPT_COLOR_2, KNOCKER_OPTION_TOKEN);
      fprintf (fp, "%s%cbright\n", KNOCKER_CONF_OPT_COLOR_2_ATTR, KNOCKER_OPTION_TOKEN);
      fprintf (fp, "\n");
    }

  fprintf (stdout, "done.\n");
  fprintf (stdout, "Configuration written to: %s\n", conf_file);
  fprintf (stdout, "You can also edit this file manually.\n");
  fprintf (stdout, "\n");

  free (conf_file);
  fclose (fp);

  return 0;
}

void knocker_conf_configure (void)
{
  char *buff = NULL;

  int use_colors = 1;           /* default is yes */

  char *color1 = NULL;
  char *color2 = NULL;
  char *color1_attr = NULL;
  char *color2_attr = NULL;

  fprintf (stdout, "\n");
  fprintf (stdout, "Welcome to the %s configuration !\n", PACKAGE);
  fprintf (stdout, "\n");
  fprintf (stdout, "%s is able to output text using colors,\n", PACKAGE);
  fprintf (stdout, "do you want me te enable colors ?\n");
  fprintf (stdout, "[Y/n]: ");

  while (1)
    {

      buff = _get_answer (buff);

      if (_isyes (buff))
        {
          use_colors = 1;
          break;
        }
      else if (_isno (buff))
        {
          use_colors = 0;
          knocker_conf_write (use_colors, color1, color2, color1_attr, color2_attr);
          return;
        }
      else
        fprintf (stdout, "[Y/n]: ");
    }


  fprintf (stdout, "\n");
  fprintf (stdout, "It is also possible to change the default colors settings,\n");
  fprintf (stdout, "do you want to change the default colors ?\n");
  fprintf (stdout, "[y/N]: ");

  while (1)
    {

      buff = _get_answer (buff);

      if (_isyes (buff))
        {

          fprintf (stdout, "\n");
          fprintf (stdout, "Normal text:\n");
          fprintf (stdout, "Choose the color you want to use for normal text:\n");
          fprintf (stdout, "[black/red/green/yellow/blue/magenta/cyan/white]: ");

          color1 = malloc (strlen (_get_answer (buff) + 1));
          strcpy (color1, buff);

          fprintf (stdout, "\n");
          fprintf (stdout, "Choose the color attribute you want to use for normal text:\n");
          fprintf (stdout, "[normal/bright/underline/blink/reverse]: ");

          color1_attr = malloc (strlen (_get_answer (buff) + 1));
          strcpy (color1_attr, buff);


          fprintf (stdout, "\n");
          fprintf (stdout, "Highlighted text:\n");
          fprintf (stdout, "Choose the color you want to use for highlighted  text:\n");
          fprintf (stdout, "[black/red/green/yellow/blue/magenta/cyan/white]: ");

          color2 = malloc (strlen (_get_answer (buff) + 1));
          strcpy (color2, buff);

          fprintf (stdout, "\n");
          fprintf (stdout, "Choose the color attribute you want to use for normal text:\n");
          fprintf (stdout, "[normal/bright/underline/blink/reverse]: ");

          color2_attr = malloc (strlen (_get_answer (buff) + 1));
          strcpy (color2_attr, buff);

          knocker_conf_write (use_colors, color1, color2, color1_attr, color2_attr);

          free (color1);
          free (color2);
          free (color1_attr);
          free (color2_attr);
          return;
        }
      else if (_isno (buff))
        {
          use_colors = 0;
          break;
        }
      else
        fprintf (stdout, "[Y/n]: ");
    }

  

  return;
}
