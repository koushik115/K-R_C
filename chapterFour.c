#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE	1000

int getLine(char *line, int max);
int strindex(const char *source, const char *searchfor);
int strrindex(const char *source, const char *searchfor);

char *pattern = "ould";

int main(void) {
	char line[MAXLINE];
	int found = 0;

	while((getLine(line, MAXLINE) > 0)) {
		if(strindex(line, pattern) >= 0) {
			printf("%s\n", line);
			found++;
		}
	}

	return found;
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
        





