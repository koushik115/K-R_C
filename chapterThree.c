#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void reverse(char *s); 
int binsearch(int x, int *v, int n);
int efficientbinsearch(int x, int *v, int n);
void escape(char *s, const char *t);
void expand(const char *s1, char *s2);
void itoa(int n, char *s);
void itob(int n, char *s, int b);
void itoawidth(int n, char *s, int w);
int trim(char *s);

int main(void) {
	/******************************* Exercise 3-1 **********************************/
	/* ---------- Test Set 1: Basic correctness ---------- */
	int v1[] = {1, 3, 5, 7, 9};
	printf("Test 1  (x=5):  %d\t%d\n", binsearch(5, v1, 5), efficientbinsearch(5, v1, 5));
	printf("Test 2  (x=1):  %d\t%d\n", binsearch(1, v1, 5), efficientbinsearch(1, v1, 5));
	printf("Test 3  (x=9):  %d\t%d\n", binsearch(9, v1, 5), efficientbinsearch(9, v1, 5));

	/* ---------- Test Set 2: Not-found cases ---------- */
	int v2[] = {10, 20, 30, 40};
	printf("Test 4  (x=5):  %d\t%d\n", binsearch(5, v2, 4), efficientbinsearch(5, v2, 4));
	printf("Test 5  (x=50): %d\t%d\n", binsearch(50, v2, 4), efficientbinsearch(50, v2, 4));
	printf("Test 6  (x=25): %d\t%d\n", binsearch(25, v2, 4), efficientbinsearch(25, v2, 4));

	/* ---------- Test Set 3: Single-element arrays ---------- */
	int v3[] = {7};
	printf("Test 7  (x=7):  %d\t%d\n", binsearch(7, v3, 1), efficientbinsearch(7, v3, 1));
	printf("Test 8  (x=3):  %d\t%d\n", binsearch(3, v3, 1), efficientbinsearch(3, v3, 1));

	/* ---------- Test Set 4: Two-element arrays ---------- */
	int v4[] = {3, 7};
	printf("Test 9  (x=3):  %d\t%d\n", binsearch(3, v4, 2), efficientbinsearch(3, v4, 2));
	printf("Test 10 (x=7):  %d\t%d\n", binsearch(7, v4, 2), efficientbinsearch(7, v4, 2));
	printf("Test 11 (x=5):  %d\t%d\n", binsearch(5, v4, 2), efficientbinsearch(5, v4, 2));

	/* ---------- Test Set 5: Edge-invariant breakers ---------- */
	int v5[] = {1, 2, 3, 4, 5, 6};
	printf("Test 12 (x=3):  %d\t%d\n", binsearch(3, v5, 6), efficientbinsearch(3, v5, 6));
	printf("Test 13 (x=6):  %d\t%d\n", binsearch(6, v5, 6), efficientbinsearch(6, v5, 6));
	printf("Test 14 (x=1):  %d\t%d\n", binsearch(1, v5, 6), efficientbinsearch(1, v5, 6));

	/* ---------- Test Set 6: Duplicates (optional but informative) ---------- */
	int v6[] = {1, 2, 2, 2, 3};
	printf("Test 15 (x=2):  %d\t%d\n", binsearch(2, v6, 5), efficientbinsearch(2, v6, 5));
	printf("Test 16 (x=4):  %d\t%d\n", binsearch(4, v6, 5), efficientbinsearch(4, v6, 5));
	/*****************************************************************************************/

	/****************************************************************************************/
	/*
	int c, nwhite = 0, nother = 0, ndigit[10] = {0};
	while((c = getchar()) != EOF) {
		switch(c) {
			case '0': case '1': case '2': case '3': case '4': 
			case '5': case '6': case '7': case '8': case '9':
				ndigit[c - '0']++;
				break;

			case ' ':
			case '\t':
			case '\n':
				nwhite++;
				break;

			default:
				nother++;
				break;
		}
	}

	printf("digits = ");
	for(int i = 0; i < 10; i++) printf(" %d", ndigit[i]);
	printf(", Whitespace = %d, other = %d\n", nwhite, nother);
	*/
	/************************************************************************************************/

	/*************************************** Exercise 3-2 ******************************************/
	char *s = (char *)malloc(strlen("This\tis\tan\texample\tstring\n") + 1);
	const char *t = "This\tis\tan\texample\tstring\n";
	escape(s, t);
	printf("%s\n", s);
	free(s);
	/**************************************************************************************************/


	return 0;
}

void reverse(char *s) {
	for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		char temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

int binsearch(int x, int *v, int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;

	while(low <= high) {
		mid = (low + high) / 2;
		if(v[mid] > x) {
			high = mid - 1;
		} else if(v[mid] < x) {
			low = mid + 1;
		} else
			return mid;
	}

	return -1;
}

int efficientbinsearch(int x, int *v, int n) {
	int low, mid, high;

	low = 0;
	high = n - 1;

	while(low <= high) {
		mid = (low + high) / 2;
		if(v[mid] > x) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	mid = (low + high) / 2;
	
	if(v[mid] == x) return mid;

	return -1;
}

void escape(char *s, const char *t) {
	char c;

	while(c = *t) {
		switch(c) {
			case '\t':
				*s++ = '\\';
				*s = 't';
				break;

			case '\n':
				*s++ = '\\';
				*s = 'n';
				break;

			default:
				*s = *t;
		}
		s++; t++;
	}
	*s = '\0';
}

void expand(const char *s1, char *s2) {
    /* -a-z */
    char firstChar = 0, lastChar = 0;
    int alphaPresent = 0, numPresent = 0;
    int i = 0, j = 0, k = 0;
    
    /* Skip the whitespace */
    for(i = 0; (isspace(s1[i]) || s1[i] == '-') && !(isalpha(s1[i]) || isdigit(s1[i])); i++);
    
    firstChar = s1[i];
    if(isalpha(s1[i])) {
        for(j = i; s1[j] != '\0'; j++) {
            if(isalpha(s1[j])) lastChar = s1[j];
            else if(isdigit(s1[j])) numPresent = 1;
        }
    } else if(isdigit(s1[i])) {
        for(j = i; s1[j] != '\0'; j++) {
            if(isdigit(s1[j])) lastChar = s1[j];
            else if(isalpha(s1[j])) alphaPresent = 1;
        }        
    }void expand(const char *s1, char *s2) {
    /* -a-z */
    char firstChar = 0, lastChar = 0;
    int alphaPresent = 0, numPresent = 0;
    int i = 0, j = 0, k = 0;
    
    /* Skip the whitespace */
    for(i = 0; (isspace(s1[i]) || s1[i] == '-') && !(isalpha(s1[i]) || isdigit(s1[i])); i++);
    
    firstChar = s1[i];
    if(isalpha(s1[i])) {
        for(j = i; s1[j] != '\0'; j++) {
            if(isalpha(s1[j])) lastChar = s1[j];
            else if(isdigit(s1[j])) numPresent = 1;
        }
    } else if(isdigit(s1[i])) {
        for(j = i; s1[j] != '\0'; j++) {
            if(isdigit(s1[j])) lastChar = s1[j];
            else if(isalpha(s1[j])) alphaPresent = 1;
        }        
    }
    
    while(firstChar <= lastChar) {
        s2[k++] = firstChar++;
    }
    
    firstChar = 0; lastChar = 0;
    if(numPresent) {
        for(i = 0; s1[i] != '\0'; i++) {
            if(isdigit(s1[i])) {
                if(!firstChar) firstChar = s1[i];
                lastChar = s1[i];
            }
        }
    } else if(alphaPresent) {
        for(i = 0; s1[i] != '\0'; i++) {
            if(isalpha(s1[i])) {
                if(!firstChar) firstChar = s1[i];
                lastChar = s1[i];
            }
        }        
    }
    
    while(firstChar <= lastChar) {
        s2[k++] = firstChar++;
    } 
    
    s2[k] = '\0';
}
    
    while(firstChar <= lastChar) {
        s2[k++] = firstChar++;
    }
    
    firstChar = 0; lastChar = 0;
    if(numPresent) {
        for(i = 0; s1[i] != '\0'; i++) {
            if(isdigit(s1[i])) {
                if(!firstChar) firstChar = s1[i];
                lastChar = s1[i];
            }
        }
    } else if(alphaPresent) {
        for(i = 0; s1[i] != '\0'; i++) {
            if(isalpha(s1[i])) {
                if(!firstChar) firstChar = s1[i];
                lastChar = s1[i];
            }
        }        
    }
    
    while(firstChar <= lastChar) {
        s2[k++] = firstChar++;
    } 
    
    s2[k] = '\0';
}

void itoa(int n, char *s) {
	int i = 0, sign;

    	sign = (n < 0) ? -1 : 1;
    
	do {
	    	if(sign < 0) s[i++] = (n % 10 + '0') - ((n % 10) * 2);
        	else s[i++] = n % 10 + '0';
	} while((n /= 10) != 0);

	if(sign < 0) s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}

void itob(int n, char *s, int b) {
    int i = 0, num = 0;
    
    /* base 2, base 8, base 10, base 16  */
    switch(b) {
        case 2:
            do {
                s[i++] = n % 2 + '0'; 
            } while((n /= 2) > 0);
            s[i] = '\0';
            break;
            
        case 8:
            do {
                num = num * 10 + n % 8;
                s[i++] = num + '0';
            } while((n /= 8) > 0);
            s[i] = '\0';
            reverse(s);
            break;
            
        case 10:
            do {
                num = num * 10 + n % 10;
                s[i++] = num + '0';
            } while((n /= 10) > 0);
            s[i] = '\0';
            reverse(s);
            break;
            
        case 16:
            do {
                if((num = num * 10 + num % 16) >= 10 && num <= 15)
                    s[i++] = num + '0' + 55;
                else if(num >= 0 && num <= 9)
                    s[i++] = num + '0';
            } while((n /= 16) > 0);
            reverse(s);
            break;
    }
}

void itoawidth(int n, char *s, int w) {
	int i = 0, sign, numOfChar = 0;

    	sign = (n < 0) ? -1 : 1;
    	if(sign < 0) numOfChar++;
    
	do {
	    	if(sign < 0) s[i++] = (n % 10 + '0') - ((n % 10) * 2);
        	else s[i++] = n % 10 + '0';
        	numOfChar++;
	} while((n /= 10) != 0);

	if(sign < 0) s[i++] = '-';
	for(int j = 0; j < (w - numOfChar); j++) s[i++] = ' ';

	s[i] = '\0';

	reverse(s);
} 

int trim(char *s) {
	int n;

	for(n = strlen(s) - 1; n >= 0; n--) {
		if(s[n] != ' ' && s[n] != '\n' && s[n] != '\t') break;
	}
	s[n + 1] = '\0';

	return n;
}
