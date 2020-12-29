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

#ifdef __WIN32__

#else

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#endif /* __WIN32__ */

#include "knocker_core.h"
#include "knocker_args.h"
#include "knocker_user.h"

#define KNOCKER_USER_DIR PACKAGE
#define KNOCKER_LASTSCAN_FILE   "lastscan"
#define KNOCKER_TOKEN  "|"

static int _dir_exists (const char *path);
static int _dir_create (const char *path);
static int _file_exists (const char *path);
static int _file_readline (FILE * fp, char *line, int maxlen);


int knocker_user_init (knocker_user_t * user)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_user_init() called.\n");
#endif

  if (knocker_user_get_username () != NULL)
    {

      if (user->name != NULL)
        user->name = realloc (user->name, strlen (knocker_user_get_username ()) + 1);
      else
        user->name = malloc (strlen (knocker_user_get_username ()) + 1);
    }

  user->name = knocker_user_get_username ();

  if (user->dir != NULL)
    user->dir = realloc (user->dir, strlen (knocker_user_get_userhome ()) + strlen (KNOCKER_USER_DIR) + 3);
  else
    user->dir = malloc (strlen (knocker_user_get_userhome ()) + strlen (KNOCKER_USER_DIR) + 3);

  strcpy (user->dir, knocker_user_get_userhome ());
  strcat (user->dir, "/.");
  strcat (user->dir, KNOCKER_USER_DIR);

  if (!_dir_exists (user->dir))
    {
      _dir_create (user->dir);
    }

  if (knocker_user_is_root)
    user->super = 1;
  else
    user->super = 0;

#ifdef DEBUG
  fprintf (stderr, "debug: username is:  %s\n", user->name);
#endif

  return 0;
}


void knocker_user_free (knocker_user_t * user)
{
#ifdef DEBUG
  fprintf (stderr, "debug: function knocker_user_free() called.\n");
#endif
/* This causes Segmentation Fault ... 	
  if ( user->name  != NULL)
    free(user->name);

  if (user->dir != NULL)
    free (user->dir);
*/
  user->super = 0;


}


int knocker_user_is_root (void)
{
#ifdef __WIN32__
  return (1);
#else
  if (getuid () == 0)
    /* user is root */
    return 1;

#endif /* __WIN32__ */

  return 0;
}


char *knocker_user_get_username (void)
{
#ifdef __WIN32__
  return (NULL);
#else

  if (getenv ("USER") != NULL)  /* the USER variable is not present in some    */
    return (getenv ("USER"));   /* Linux distribution. LOGNAME should be there. */

  else if (getenv ("LOGNAME") != NULL)
    return (getenv ("LOGNAME"));

  else
    return (NULL);

#endif /* __WIN32__ */
}


char *knocker_user_get_userhome (void)
{
#ifdef __WIN32__
  return (NULL);
#else
  return (getenv ("HOME"));
#endif /* __WIN32__ */
}



/* ---- internally used functions -------------- */
static int _dir_create (const char *path)
{
#ifdef __WIN32__
  return (0);
#else

  /* first let's check if the directory exists already */
  if (_dir_exists (path))
    return 0;                   /* directory exist, no need to create it again */

  /* 0700 Allow only the user to read, write, and execute */
  if (mkdir (path, 0700) != 0)
    return -1;                  /* couldn't create dir */

#endif /* __WIN32__ */

  return 0;
}

static int _dir_exists (const char *path)
{
#ifdef __WIN32__

#else
  struct stat dirstat;

  if (stat (path, &dirstat) != 0)
    {
      /* couln't access to directory */
      return 0;
    }

  if (S_ISDIR (dirstat.st_mode))
    {
      /* directory exist and "it's a directory" */
      return 1;
    }
#endif /* __WIN32__ */

  return 0;
}

static int _file_exists (const char *path)
{
#ifdef __WIN32__

#else
  struct stat filestat;

  if (stat (path, &filestat) != 0)
    {
      /* coulnd't access to file */
      return 0;
    }

  if (S_ISREG (filestat.st_mode))
    {
      /* file exist and "it's a regular file" */
      return 1;
    }
#endif /* __WIN32__ */
  return 0;
}

static int _file_readline (FILE * fp, char *line, int maxlen)
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
