#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES    5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void Qsort(void *lineptr[], int left, int right, int (*cmp)(void *, void *));
int mycmp(char *s1, char *s2);
int numcmp(char *s1, char *s2);

int numeric = 0, reverse = 0;
    
int main(int argc, char **argv)
{
    int nlines;
    
    if(argc > 1) {
        while(*++argv != NULL) {
            if(strcmp(*argv, "-n") == 0)
                numeric = 1;
            else if(strcmp(*argv, "-r") == 0)
                reverse = 1;
        }
    }
    
    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        Qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))mycmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort!\n");
        return 1;
    }
    return 0;
}


#define MAXLEN  1000

int getLine(char *line, int maxline);
char *alloc(int n);

int readlines(char *lineptr[], int maxline) {
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while((len = getLine(line, MAXLEN)) > 0) {
        if(nlines >= maxline || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    
    return nlines;
}

#define ALLOCSIZE   1000
char allocbuffer[ALLOCSIZE];
char *allocp = allocbuffer;

int getLine(char *line, int maxline) {
    int c, i;
    
    for(i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
        
    if(c == '\n')
        line[i++] = c;
        
    line[i] = '\0';
    
    return i;
}

char *alloc(int n) {
    if((allocbuffer + ALLOCSIZE - allocp) >= n) {
        allocp += n;
        return allocp - n;
    } else 
        return NULL;
}

void writelines(char *lineptr[], int nlines) {
    for(int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void Qsort(void *v[], int left, int right, int (*cmp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int i, int j);
    
    if(left >= right)
        return;
        
    swap(v, left, (left + right) / 2);
    last = left;
    for(i = left + 1; i <= right; i++) {
        if((*cmp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    
    swap(v, left, last);
    Qsort(v, left, last - 1, cmp);
    Qsort(v, last + 1, right, cmp);
}

int mycmp(char *s1, char *s2) {
    int result;
    
    if(numeric) {
        result = numcmp(s1, s2);
    } else {
        result = strcmp(s1, s2);
    }
    
    if(reverse)
        return -result;
    else
        return result;
}

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    
    if(v1 < v2) return -1;
    else if(v1 > v2) return 1;
    else return 0;
}

void swap(void *v[], int i, int j) {
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
