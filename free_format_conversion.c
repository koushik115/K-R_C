#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define SIZE	5

int getch(void);
void ungetch(int c);

int main(void) {
	int n, array_int[SIZE], getint(int *pn), getfloat(float *pn);
	float array_float[SIZE];

	for(n = 0; n < SIZE && getint(&array_int[n]) != EOF; n++);

	for(n = 0; n < SIZE; n++)
		printf("%d\n", array_int[n]);

	for(n = 0; n < SIZE && getfloat(&array_float[n]) != EOF; n++);

	for(n = 0; n < SIZE; n++)
		printf("%f\n", array_float[n]);	

	return 0;
}


int getint(int *pn) {
	int c, sign;

	while(isspace(c = getch()));

	if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
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

	for(*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}

	*pn *= sign;
	if(c != EOF)
		ungetch(c);

	return c;
}

int getfloat(float *pn) {
	int c, sign;
	int isdec = 0, factor = 1;

	while(isspace(c = getch()));

	if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if(c == '-' || c == '+' || c == '.') {
		isdec = (c == '.') ? 1 : 0;	
		int d = getch();
		if(!isdigit(d)) {
			ungetch(d);
			ungetch(c);
			return 0;
		}
		
		c = d;
	}

	for(*pn = 0.0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
		if(isdec)
			factor *= 10;
	}

	if(c == '.' && !isdec) {
		int d = getch();
		if(!isdigit(d)) {
			ungetch(d);
			ungetch(c);
			return 0;
		}

		c = d;
	}

	for(; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
		factor *= 10;
	}

	*pn = (*pn * sign) / (float)factor;
	if(c != EOF)
		ungetch(c);
	return c;
}

#define BUFFER_SIZE	1000
int buffer[BUFFER_SIZE];
int bufferp = -1;

int getch(void) {
	return (bufferp >= 0) ? buffer[bufferp--] : getchar();
}

void ungetch(int c) {
	if (bufferp < BUFFER_SIZE - 1)
		buffer[++bufferp] = c;
}
