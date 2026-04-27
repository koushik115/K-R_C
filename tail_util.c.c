#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN    100

int getLine(char *line, int max);

int main(int argc, char **argv)
{
    int line_to_print = 0;
    int line_no = 0;
    int total_lines = 0;
    char **line;
    
    if(argc > 1) {
        if(argv[1][0] == '-') {
            line_to_print = atoi(&argv[1][1]);
            if(line_to_print <= 0)
                line_to_print = 10;
        }
        else
            line_to_print = 10;
    } else
        line_to_print = 10;
        
    line = (char **)malloc(line_to_print * sizeof(char *));
    for(int i = 0; i < line_to_print; i++)
        line[i] = (char *)malloc(MAXLEN);
        
    while(getLine(line[line_no], MAXLEN) > 0) {
        total_lines++;
        line_no = (line_no + 1) % line_to_print;
    }
    
    if(total_lines < line_to_print) {
        for(int i = 0; i < total_lines; i++)
            printf("%s", line[i]);
    } else {
        for(int i = line_no; i < line_to_print; i++)
            printf("%s", line[i]);
            
        for(int i = 0; i < line_no; i++)
            printf("%s", line[i]);
    }
    
    for(int i = 0; i < line_to_print; i++)
        free(line[i]);
        
    free(line);
        
    return 0;
}

int getLine(char *line, int max) {
    int c, i;
    
    for(i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
        
    if(c == '\n')
        line[i++] = c;
        
    line[i] = '\0';
    
    return i;
}