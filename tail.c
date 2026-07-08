#include <stdio.h>
#include <string.h>

#define MAXLINES    10
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxline);
//void writelines(char *lineptr[], int maxline);

int main(int argc, char *argv[])
{
    int nlines, c;
    int nlinesToPrint = 10;
    
    while(--argc > 0 && (*++argv)[0] == '-') {
	char *p = argv[0];
        while(c = *++p) {
            if(c >= '0' && c <= '9') {
                nlinesToPrint = nlinesToPrint * 10 + (c - '0');
            }
        }
    }
    
    while((nlines = readlines(lineptr, MAXLINES)) > 0) {
        if(nlines >= nlinesToPrint) {
            for(int i = (nlines - nlinesToPrint); i < nlines; i++) {
                printf("%s\n", lineptr[i]);
            }
        } else {
            for(int i = 0; i < nlines; i++) {
                printf("%s\n", lineptr[i]);
            }            
        }
    }
    return 0;
}

#define MAXLEN  1000
int getLine(char *line, int maxlen);
char *alloc(int size, int reset);

int readlines(char *lineptr[], int maxline) {
    int len = 0, nlines = 0;
    char *p, line[MAXLEN];
    int idx = 0;

    while((len = getLine(line, MAXLEN)) > 0) {
        if((p = alloc(len, (idx == 0))) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
	    nlines++;
            lineptr[idx] = p;
	    idx = (idx + 1) % maxline;
        }
    }
    
    return (nlines > maxline) ? maxline : nlines;
}

int getLine(char *line, int maxlen) {
    int c = 0, i;
    
    for(i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }

    if(c == '\n') {
	    line[i++] = c;
    }

    line[i] = '\0';
    return i;
}

#define ALLOCSIZE   1000
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int size, int reset) {
    if (reset) allocp = allocbuf;
    if((allocbuf + ALLOCSIZE - allocp) >= size) {
        allocp += size;
        return allocp - size;
    } else {
	    return NULL;
    }
}
