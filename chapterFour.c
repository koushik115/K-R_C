#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE	1000
#define MAXOP	100
#define MAXVAL	100
#define BUFSIZE	100
#define NUMBER  '0'

int getLine(char *line, int max);
int strindex(const char *source, const char *searchfor);
int strrindex(const char *source, const char *searchfor);

void infixCalculator(void);
int getop(char *s);
void push(double f);
double pop(void);



char *pattern = "ould";

int main(void) {
	/*
	char line[MAXLINE];
	int found = 0;

	while((getLine(line, MAXLINE) > 0)) {
		if(strindex(line, pattern) >= 0) {
			printf("%s\n", line);
			found++;
		}
	}

	return found;
	*/

	/* Algo for infix (Reverse Polish) calculator */
	/* while (next operator or opearand is not EOF)
	 * 	if (number)
	 * 		push it
	 * 	else if (operator)
	 * 		pop operands
	 * 		do operations
	 * 		push result
	 * 	else if (new line)
	 * 		pop and print the top of the stack
	 * 	else
	 * 		error
	 */

	infixCalculator();
}

int getLine(char *line, int max) {
	int c, i;

	i = 0;
	while(--max > 0 && (c = getchar()) != EOF && c != '\n') {
		line[i++] = c;
	}

	if(c == '\n')
		line[i++] = c;

	line[i] = '\0';
}

int strindex(const char *source, const char *searchfor) {
	int i, j, k;

	for(i = 0; i < source[i] != '\0'; i++) {
		for(j = i, k = 0; searchfor[k] != '\0' && source[j] != '\0' && source[j] == searchfor[k]; j++, k++);
		if(k > 0 && searchfor[k] == '\0')
			return i;
	}

	return -1;
}


int strrindex(const char *source, const char *searchfor) {
	int i, j, k;
    int rightmost = -1;
    
    if ((*source == '\0' && *searchfor != '\0'))
        return rightmost;
    else if (*source == '\0' && *searchfor == '\0') 
        return 0;
        
	for(i = 0; source[i] != '\0'; i++) {
		for(j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k]; j++, k++);
		if(k > 0 && searchfor[k] == '\0') 
		    rightmost = i;
	}
	
	return rightmost;
}

double asciiToFloat(const char *s) {
    double val, power, exponent = 1.0;
    int i, sign, expsign;
    
    for(i = 0; isspace(s[i]); i++);
    
    sign = (s[i] == '-') ? -1 : 1;
    
    if(s[i] == '+' || s[i] == '-')
        i++;
        
    for(val = 0.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
    }
    
    if(s[i] == '.') 
        i++;
        
    for(power = 1.0; isdigit(s[i]); i++) {
        val = val * 10.0 + (s[i] - '0');
        power *= 10.0;
    }
    
    if(s[i] == 'e' || s[i] == 'E')
        i++;
        
    expsign = (s[i] == '-') ? -1 : 1;
    
    if(s[i] == '-' || s[i] == '+')
        i++;
        
    int loopcounter = 0;
    for(; isdigit(s[i]); i++)
	loopcounter = loopcounter * 10 + (s[i] - '0');
    
    for(int k = 0; k < loopcounter; k++) {
        if (expsign == -1) {
            exponent /= 10.0;
        } else {
            exponent *= 10.0;
        }
    }
    
    return sign * val * exponent / power;
}

void infixCalculator(void) {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(asciiToFloat(s));
			break;

		case '+':
			push(pop() + pop());
			break;
		
		case '*':
			push(pop() * pop());
			break;

		case '-':
			op2 = pop();
			push(pop() - op2);
			break;

		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;

		case '%':
			op2 = pop();
			if (op2 != 0.0)
			    push((int)pop() % (int)op2);
			else
			    printf("error: zero divisor\n");
			break;

		case '\n':
			printf("\t%.8g\n", pop());
			break;

		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else 
		printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else 
		printf("error: stack empty\n");

	return 0.0;
}

int getch(void);
void ungetch(int c);


// int getop(char *s) {
// 	int i, c;

// 	while ((s[0] = c = getch()) == ' ' || c == '\t');
//         s[1] = '\0';
	
// 	if (!isdigit(c) && c != '.')
// 		return c;

// 	i = 0;
// 	if (isdigit(c))
// 		while(isdigit(s[++i] = c = getch()));
	
// 	if (c == '.')
// 		while(isdigit(s[++i] = c = getch()));

// 	s[i] = '\0';
	
// 	if (c != EOF) 
// 		ungetch(c);

// 	return NUMBER;
// }


int getop(char *s) {
    int i = 0, c, previousValue = 0;
    
    while((s[0] = c = getch()) == ' ' || c == '\t')
    s[1] = '\0';
    
    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            previousValue = c;
            s[++i] = c = getch();
            if (isdigit(c))
                while(isdigit(s[++i] = c = getch()));
            else {
                ungetch(c);
                return previousValue;
            }
        } else {
            return c;
        }
    }
    
    if (isdigit(c))
        while(isdigit(s[++i] = c = getch()));
        
    if(c == '.')
        while(isdigit(s[++i] = c = getch()));
        
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
        
    return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}



