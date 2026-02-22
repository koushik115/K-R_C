#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 100
#define ALLOCSIZE   10000

void swap(int *px, int *py);

int getch(void);
void ungetch(int c);

int strLen(char *s);
void strCpy(char *s, const char *t);
int strCmp(const char *s, const char *t);
void strCat(char *s, const char *t);
int strEnd(char *s, const char *t);
void strCpyByWidth(char *s, const char *t, int width);
void strCatByWidth(char *s, const char *t, int width);
int strCmpByWidth(char *s, const char *t, int width);

// int main(void) {
//     int n, array[SIZE], getint(int *);
//     double arrayFloat[SIZE], getfloat(double *);
//      /*
//     for(int i = 0; i < SIZE; i++)
//         array[i] = -1;

//     for(n = 0; n < SIZE && getint(&array[n]) != EOF; n++);

//     for(int i = 0; i < SIZE; i++)
//         if(array[i] >= 0) printf("%d\t", array[i]);
//     */

//     for(int i = 0; i < SIZE; i++)
//         arrayFloat[i] = -1.0;

//     for(n = 0; n < SIZE && getfloat(&arrayFloat[n]) != EOF; n++);

//     for(int i = 0; i < SIZE; i++)
//         if(arrayFloat[i] >= 0.0) printf("%f\t", arrayFloat[i]);
//}

int main(void) {
	int n, getint(int *);
	int status;
	float f, getfloat(float *);

// 	printf("Enter test input (Ctrl+D to end):\n");

// 	while ((status = getint(&n)) != EOF) {
// 		if (status == 0) {
// 			printf("Not a number\n");
// 			getch();   // discard one character
// 		} else {
// 			printf("Read integer: %d\n", n);
// 		}
// 	}
    while ((status = getfloat(&f)) != EOF) {
        if (status == 0) {
            printf("Not a float\n");
            getch();
        }
        else
            printf("Read float: %.6f\n", f);
    }


	printf("EOF reached\n");
	return 0;
}

void swap(int *px, int *py) {
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}



int getint(int *pn) {
	int c, sign;

	while(isspace(c = getch()));

	if(!isdigit(c) && c != '-' && c != '+') {
		if (c != EOF) {
			ungetch(c);
			return 0;
		} else {
			return EOF;
		}

	}

	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		int d = getch();
		if(!isdigit(d)) {
			ungetch(d);
			ungetch(c);
			return 0;
		}

		c = d;
	}

	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	else {
		return EOF;
	}

	return c;
}

float getfloat(float *pn) {
	int c, sign;
	float decimal = 1.0;
	while(isspace(c = getch()));

	if (!isdigit(c) && c != '+' && c != '-' && c != '.' && c != EOF) {
		if (c != EOF) {
			ungetch(c);
			return 0;
		} else {
			return EOF;
		}
	}

	sign  = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+' || c == '.') {
		int d = getch();
		if(!isdigit(d)) {
			ungetch(d);
			ungetch(c);
			return 0;
		}
        if (c == '.') decimal *= 10.0;
		c = d;
	}

	for(*pn = 0.0; isdigit(c); c = getch()) {
		*pn = *pn * 10.0 + (c - '0');
	}

	if (c == '.') {
		c = getch();
	}

	for(; isdigit(c); c = getch()) {
		*pn = *pn * 10.0 + (c - '0');
		decimal *= 10.0;
	}

	*pn *= sign / decimal;
	if (c != EOF)
		ungetch(c);

	return c;
}

int buffer[SIZE];
int buffp = 0;

int getch(void) {
	return (buffp > 0) ? buffer[--buffp] : getchar();
}
void ungetch(int c) {
	if (buffp < SIZE)
		buffer[buffp++] = c;
	else
		printf("error: buffer overflow!!\n");
}

int strLen(char *s) {
    char *p = s;
    
    while(*p != '\0') p++;
    
    return p - s;
}

void strCpy(char *s, const char *t) {
    while(*s++ = *t++);
}

int strCmp(const char *s, const char *t) {
    for(; *s == *t; s++, t++) {
        if (*s == '\0')
            return 0;
    }
    
    return *s - *t;
}

void strCat(char *s, const char *t) {
    while(*s) s++;
    while(*s++ = *t++);
}

int strEnd(char *s, const char *t) {
    const char *tCopy = t;
    const char *sCopy = s;
    int tCount = 0;
    int sCount = 0;
    
    while(*tCopy) {
        tCount++;
        tCopy++;
    }
    
    while(*sCopy) {
        sCount++;
        sCopy++;
    }
    
    if (tCount > sCount) return 0;
    
    while(*s != '\0')
        s++;
    s -= tCount;
    
    for(; *s == *t; s++, t++) {
        if (*s == '\0')
            return 1;
    }
    
    return 0;
}

void strCpyByWidth(char *s, const char *t, int width) {
    while((*s = *t) && width > 0) {
        s++;
        t++;
        width--;
    }
    
    if(*s != '\0' && width == 0) *s = '\0';
}

void strCatByWidth(char *s, const char *t, int width) {
    while(*s) s++;
    
    while((*s = *t) && width > 0) {
        s++;
        t++;
        width--;
    }
    
    if(*s != '\0' && width == 0) *s = '\0';
}

int strCmpByWidth(char *s, const char *t, int width) {
    for(; (*s == *t) && width > 0; s++, t++, width--) {
        if (*s == '\0')
            return 0;
    }
    
    return (width == 0) ? 0 : (*s - *t);
}


/*
*   Memory Allocator and De-allocator
*/
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int n) {
    if ((allocbuf + ALLOCSIZE - allocp) >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}

void afree(char *p) {
    if (p >= allocbuf && p < (allocbuf + ALLOCSIZE))
        allocp = p;
}
