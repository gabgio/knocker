#include <stdio.h>
#include <string.h>


#define MAXLINELEN   400
#define COMMENT_CHAR '#'

#define SERVICES_FILE   "/etc/services"
#define SERVICES_HEADER "knocker_core_services_db.h"
#define SERVICES_ARRAY  "knocker_core_services_db"
#define TEMPFILE        "temp"

int last_port       = 0;
int total_services  = 0;
int max_service_len = 0;


int dumb_fgetline (FILE * fp, char *line, int maxlen)
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


int dumb_fcopy_but_append (const char *src, const char *dst)
{
  FILE *srcfp, *dstfp;
  
  int c;

  srcfp = fopen (src, "r");
  
  if (srcfp == NULL)
    exit (1);
        
  dstfp = fopen (dst, "a");
          
   if (dstfp == NULL)
     {
        fclose (srcfp);
        exit (1);
     }
     
   do {
        fputc(fgetc(srcfp), dstfp);
  } while (!feof(srcfp));  
     
  fclose(srcfp);
  fclose(dstfp);                                 
}


int is_line_commented (FILE * fp, char *line, const char c)
{
   if (line[0] == c) 
     return 1;
   
   return 0;
}

int is_a_blank_space (char c)
{
  if(( c == ' ') || ( c != '\t'))
   return 1;
   
  return 0;
}

int get_things_from_line  (const char *line, int maxlen, char *service, char *port, char *extra)
{
   int i = 0;
   
   int is = 0;
   int ip = 0;
   int ie = 0;
   
   while(line[i] != '\0')
    {
      if (!isblank(line[i]))
        {
           service[is] = line[i];
           i++;
           is++;
        }
      else
        {
          service[is] = '\0';
          break;
        }
    }
       
   while(isblank(line[i]))
    i++;
   
   while(line[i] != '\0')
    {
     if (line[i] == '/')
       break;
     
     port[ip] = line[i];
     
     ip++;
     i++;
    }
     
   port[ip] = '\0';
   
   i = i + 4; /* skips 4 chars */
   
   while(line[i] != '\0')
    {                  
     if (isblank(line[i]) && isblank(line[++i]))
       {
        i++;
       }
     else
      {
       extra[ie] = line[i];
       ie++;
       i++;
      }
   } 
   
  extra[ie] = '\0';  
   

  if (last_port == atoi(port))
    {
      return 0;   
    }

  last_port = atoi(port);
  
  return 1;  
}


int
main (int argc, char *argv[])
{
  FILE *in, *out;

  char linebuff[MAXLINELEN];
  
  char servicename[MAXLINELEN];
  char portname[MAXLINELEN];
  char extrainfo[MAXLINELEN];

  in = fopen (SERVICES_FILE, "r");

  if (in == NULL)
    exit (1);

  out = fopen (TEMPFILE, "w");

  if (out == NULL)
    {
      fclose (in);
      exit (1);
    }


  while(dumb_fgetline (in, linebuff, MAXLINELEN) != EOF)
   {
     if (linebuff[0] != '\0')
      {
        if (!is_line_commented (in, linebuff, COMMENT_CHAR))
          {
       
            if (get_things_from_line  (linebuff, MAXLINELEN, servicename, portname, extrainfo))
              {
                int temp;
/*
                fprintf(out, "  %s[%s] = malloc(%d + 1);\n",  SERVICES_ARRAY, portname, strlen(servicename));
                fprintf(out, "  strcpy(%s[%s], \"%s\");\n", SERVICES_ARRAY, portname, servicename);
		fprintf(out, "\n");
		fprintf(out, "  if( %s[%s] == NULL )\n", SERVICES_ARRAY,portname);
		fprintf(out, "    return -1;\n");
                fprintf(out, "\n");
*/
                fprintf(out, "%s:%s\n", portname, servicename);


                total_services++;
                temp = strlen(servicename);

                if ( temp > max_service_len)
                  max_service_len = temp;

              }
          }
      }
   }


  fclose(in);
  fclose(out);

  out = fopen (SERVICES_HEADER, "w");
  
  if (out == NULL)
    {
      exit (1);
    }
                            
  
  fprintf(out, "/* this file has been automagically generated from %s */\n", SERVICES_FILE);
  fprintf(out, "/* found %d service names, the longest one is %d chars long. */\n\n", total_services, max_service_len);
  fprintf(out, "const char %s[%d][%d];\n\n\n\n", SERVICES_ARRAY, max_service_len + 1, total_services + 1); 
  
  fclose(out);
  
  dumb_fcopy_but_append (TEMPFILE, SERVICES_HEADER);
  
  remove(TEMPFILE);
  
  return 0;
}
