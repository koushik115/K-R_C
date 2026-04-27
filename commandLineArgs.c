#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100
#define MAXLINE 1000

int getLine(char *line, int max);

int main(int argc, char *argv[]) {
  /*
  for (int i = 0; i < argc; i++)
          printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
  printf("\n");
  */
  /*
  while (--argc > 0)
          printf("%s%s", *++argv, (argc > 1) ? " " : "");
  printf("\n");
  */
  /*
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
          printf("Usage: find pattern\n");
  else {
          while (getLine(line, MAXLINE) > 0) {
                  if (strstr(line, argv[1]) != NULL) {
                          printf("%s", line);
                          found++;
                  }
          }
  }
  return found;
  */
  /*
          char line[MAXLINE];
          long lineno = 0;
          int c, except = 0, number = 0, found = 0;

          while(--argc > 0 && (*++argv)[0] == '-') {
                  while(c = *++argv[0]) {
                          switch(c) {
                          case 'x':
                                  except = 1;
                                  break;

                          case 'n':
                                  number = 1;
                                  break;

                          default:
                                  printf("find: illegal option %c\n", c);
                                  argc = 0;
                                  found = -1;
                                  break;
                          }
                  }
          }

          if(argc != 1) {
                  printf("Usage: find -x -n pattern\n");
          } else {
                  while(getLine(line, MAXLINE) > 0)  {
                          lineno++;
                          if((strstr(line, *argv) != NULL) != except) {
                                  if(number)
                                          printf("%ld:", lineno);
                                  printf("%s", line);
                                  found++;
                          }
                  }
          }

          return found;
          */

  int line_to_print = 0;
  int line_no = 0;
  int total_lines = 0;
  char **line;

  if (argc > 1) {
    if (argv[1][0] == '-') {
      line_to_print = argv[1][1] - '0';
      if (line_to_print <= 0)
        line_to_print = 10;
    } else
      line_to_print = 10;
  } else
    line_to_print = 10;

  line = (char **)malloc(line_to_print * sizeof(char *));
  for (int i = 0; i < line_to_print; i++)
    line[i] = (char *)malloc(MAXLEN);

  while (getLine(line[line_no], MAXLEN) > 1) {
    total_lines++;
    line_no = (line_no + 1) % line_to_print;
  }

  if (total_lines < line_to_print) {
    for (int i = 0; i < total_lines; i++)
      printf("%s", line[i]);
  } else {
    for (int i = line_no; i < line_to_print; i++)
      printf("%s", line[i]);

    for (int i = 0; i < line_no; i++)
      printf("%s", line[i]);
  }

  return 0;
}

int getLine(char *line, int max) {
  int i, c;

  for (i = 0; i < max && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;

  if (c == '\n')
    line[i++] = c;

  line[i] = '\0';
  return i;
}
