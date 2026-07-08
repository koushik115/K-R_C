#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define MAXLINES    5000

#define NUMERIC_FLAG 0x01
#define REVERSE_FLAG 0x02

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qSort(void *v[], int left, int right,
           int (*cmp)(void *, void *, uint8_t));
int compareWrapper(void *a, void *b, uint8_t flag);
int numcmp(char *s1, char *s2);
void swap(void *v[], int i, int j);

int getLine(char *line, int maxlen);
char *alloc(int n);

uint8_t flag = 0;

int main(int argc, char *argv[])
{
    int nlines = 0;
    int c;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {

            case 'n':
                flag |= NUMERIC_FLAG;
                break;

            case 'r':
                flag |= REVERSE_FLAG;
                break;

            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
        }
    }

    if (argc != 1) {
        printf("usage: sort [-n] [-r]\n");
    } else {
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            qSort((void **)lineptr, 0, nlines - 1, compareWrapper);
            writelines(lineptr, nlines);
            return 0;
        } else {
            printf("input too big to sort\n");
            return 1;
        }
    }

    return 0;
}

#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines)
{
    int nlines = 0;
    int len;
    char *p;
    char line[MAXLEN];

    while ((len = getLine(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int getLine(char *line, int maxlen)
{
    int i, c;

    for (i = 0; i < maxlen - 1 &&
                (c = getchar()) != EOF &&
                c != '\n'; i++)
        line[i] = c;

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';

    return i;
}

int compareWrapper(void *a, void *b, uint8_t flag)
{
    int numeric;
    int reverse;
    int result;

    numeric = (flag & NUMERIC_FLAG);
    reverse = (flag & REVERSE_FLAG);

    if (numeric)
        result = numcmp((char *)a, (char *)b);
    else
        result = strcmp((char *)a, (char *)b);

    if (reverse)
        return -result;

    return result;
}

void qSort(void *v[], int left, int right,
           int (*cmp)(void *, void *, uint8_t))
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++) {
        if ((*cmp)(v[i], v[left], flag) < 0)
            swap(v, ++last, i);
    }

    swap(v, left, last);

    qSort(v, left, last - 1, cmp);
    qSort(v, last + 1, right, cmp);
}

int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
