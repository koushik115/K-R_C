#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

enum boolean {NO, YES};
enum escapes {BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r'};
enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

int strLength(const char *string);
int isLeapYear(int year);
int asciiToInteger(const char *intString);
int changeToLower(const char c);
int hexToDec(const char *hex);
char *squeeze(char *s, char c);
char *concatString(char *s1, char *s2);
char *squeezeVerTwo(char *s1, const char *s2);
int any(const char *s1, const char *s2);
unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
unsigned int invert(unsigned int x, int p, int n);
unsigned int rightrot(unsigned int x, int n); 
int bitcount(unsigned int x);
int bitcountVerTwo(unsigned int x);
int changeToLowerVerTwo(const char c);

int main(void) {

	/****************************** Exercise 2-1 ******************************/
	printf("Range of signed char is from %d to %d\n", (int)((-1 * pow(2, sizeof(char) * 8) / 2)), (int)(((1 * pow(2, sizeof(char) * 8)) / 2) - 1));
	printf("Range of unsigned char is from %d to %d\n", 0, (int)(((1 * pow(2, sizeof(char) * 8) - 1)))) ;
	
	printf("Range of signed short is from %d to %d\n", (int)((-1 * pow(2, sizeof(short) * 8) / 2)), (int)(((1 * pow(2, sizeof(short) * 8)) / 2) - 1));
	printf("Range of unsigned short is from %d to %d\n", 0, (int)(((1 * pow(2, sizeof(short) * 8) - 1)))) ;

	printf("Range of signed int is from %d to %d\n", (int)((-1 * pow(2, sizeof(int) * 8) / 2)), (int)(((1 * pow(2, sizeof(int) * 8)) / 2) - 1));
	printf("Range of unsigned int is from %d to %ld\n", 0, (long)(((1 * pow(2, sizeof(int) * 8) - 1)))) ;

	printf("Range of signed long is from %ld to %ld\n", (long)((-1 * pow(2, sizeof(long) * 8) / 2)), (long)(((1 * pow(2, sizeof(long) * 8)) / 2) - 1));
	printf("Range of unsigned long is from %d to %lu\n", 0, (unsigned long)(((1 * pow(2, sizeof(long) * 8) - 1)))) ;
	/*************************************************************************************************/
	/*************************************************************************************************/
	/*
	char *exampleString = "The C Programming Language";
	printf("Size of the string is %d\n", strLength(exampleString));
	*/
	/*	
	printf("%d\t%d", isLeapYear(2024), isLeapYear(2025));
	*/
	/*************************************************************************************************/
	/******************************* Exercise 2-2 ********************************/
	const int LIMIT = 100;
	int c;
	int i = 0;
	char s[100] = {0};
	while (1) {
		if (i < LIMIT - 1) {
			if ((c = getchar()) != '\n') {
				if (c != EOF) {
					s[i++] = c;
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			break;
		}
	}
	s[i] = '\0';
	printf("%s\n", s);
	/*************************************************************************************************/
	
	/*************************************************************************************************/
	/*
	printf("%d\n", asciiToInteger("12345"));
	*/
	/*************************************************************************************************/
	/*************************************************************************************************/
	/*
	printf("%c\n", changeToLower('F'));
	*/
	/*************************************************************************************************/

	/********************************************* Exercise 2-3 *************************************/
	printf("%d\t%d\t%d\t%d\t%d\n", hexToDec("0x10fa"), hexToDec("0XBABE"), hexToDec("0xbabe"), hexToDec("0XFACE"), hexToDec("0xface"));
	/**************************************************************************************************/
	
	/***************************************************************************************************/
	/*
	char *stringExample = (char *)malloc(strlen("ExampleProgram") + 1);
	strcpy(stringExample, "ExampleProgram");
	printf("%s\n", squeeze(stringExample, 'x'));
	free(stringExample);
	*/
	/****************************************************************************************************/
	

	/*****************************************************************************************************/
    	/*
	char *concatStringEx = (char *)malloc(strlen("Hello, ") + strlen("World") + 1);
   	strcpy(concatStringEx, "Hello, ");
    	printf("%s", concatString(concatStringEx, "World!"));
    	free(concatStringEx);
	*/
	/*****************************************************************************************************/


	/********************************************** Exercise 2-4 *****************************************/
	char *s1Ex2_4 = (char *)malloc(strlen("Cat") + 1);
	strcpy(s1Ex2_4, "Cat");
	const char *s2Ex2_4 = "Dat";
	printf("%s\n", squeezeVerTwo(s1Ex2_4, s2Ex2_4));
	free(s1Ex2_4);
	/********************************************************************************************************/
	
	/********************************************** Excercise 2-5 ********************************************/
	const char *s1Ex2_5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	const char *s2Ex2_5 = "Z";
	printf("%d\n", any(s1Ex2_5, s2Ex2_5));
	/**********************************************************************************************************/

	/********************************************** Exercise 2-6 **********************************************/
	printf("%d\n", setbits(0b10100101, 4, 3, 0b00111100));
	/**********************************************************************************************************/

	/********************************************** Exercise 2-7 **********************************************/
	printf("%d\n", invert(0b101001010, 4, 3));
	/**********************************************************************************************************/

	/********************************************** Excercise 2-8 *********************************************/
	printf("%d\n", rightrot(0b10100011, 4));
	/***********************************************************************************************************/

	/********************************************** Excercise 2-9 ***********************************************/
	printf("%d\n", bitcountVerTwo(0b10010011));
	/************************************************************************************************************/

	/********************************************** Exercise 2-10 ***********************************************/
	printf("%c\n",changeToLowerVerTwo('F'));
	/*************************************************************************************************************/

	return 0;


}

int strLength(const char *string) {
	size_t length = 0;

	while(*string) {
		string++; length++;
	}

	return length;
}

int isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0); 
}

int asciiToInteger(const char *intString) {
	int integer = 0;

	while (*intString != '\0' && *intString >= '0' && *intString <= '9') {
		integer = integer * 10 + (*intString - '0');
		intString++;
	}

	return integer;
}

int changeToLower(const char c) {
	if (c >= 'A' && c <= 'Z') return c + 'a' - 'A';
	else return c;
}

int hexToDec(const char *hex) {
	int dec = 0;
	
	if (*hex == '0' && (*(hex + 1) == 'x' || *(hex + 1) == 'X'))
		hex += 2;

	while(*hex) {
		if (*hex >= '0' && *hex <= '9') {
			dec = dec * 16 + (*hex - '0');
		} else if (*hex >= 'a' && *hex <= 'f') {
			dec = dec * 16 + (*hex - 'a') + 10;
		} else if (*hex >= 'A' && *hex <= 'F') {
			dec = dec * 16 + (*hex - 'A') + 10;
		}

		hex++;
	} 

	return dec;
}

char *squeeze(char *s, char c) {
	int i = 0, j = 0;

	while(*(s + j) != '\0') {
		if (*(s + j) != c) {
		    *(s + i) = *(s + j);
		    i++; j++;
		} else j++;

	}

	*(s + i) = '\0';
	return s;
}

char *concatString(char *s1, char *s2) {
	while(*s1) s1++;
	while(*s1 = *s2) { s1++; s2++; }

	return s1;
}

char *squeezeVerTwo(char *s1, const char *s2) {
	int dontcopy = 0;
	int i, j, k = 0;

	for(i = 0; *(s1 + i) != '\0'; i++) {
		dontcopy = 0;
		for(j = 0; *(s2 + j) != '\0'; j++) {
			if(*(s1 + i) == *(s2 + j)) {
				dontcopy = 1;
				break;
			}
		}
		if(!dontcopy) {
			*(s1 + k++) = *(s1 + i);	
		}
	}
	
	*(s1 + k) = '\0';
	return s1;
}

int any(const char *s1, const char *s2) {
	int i, j;

	for(i = 0; *(s1 + i) != '\0'; i++) {
		for(j = 0; *(s2 + j) != '\0'; j++) {
			if(*(s1 + i) == *(s2 + j))
				return i;
		}
	}

	return -1;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
	int copyOfp = p;

	int extractedBits = (y & ~(~0 << n));
	for(int i = 0; i < n; i++) x &= ~(1 << p--);
	p = copyOfp;
	x |= (extractedBits << (p + 1 - n));

	return x;
}

unsigned int invert(unsigned int x, int p, int n) {
    int copyOfp = p;
    
    int invertedBits = ~x;
    int extractedBits = ((invertedBits >> (p + 1 - n)) & ~(~0 << n));
    for(int i = 0; i < n; i++) x &= ~(1 << p--);
    p = copyOfp;
    x |= (extractedBits << (p + 1 - n));
    
    return x;
}

unsigned int rightrot(unsigned int x, int n) {
    int extractedBits = (x & ~(~0 << n));
    x >>= n;
    x |= (extractedBits << ((sizeof(unsigned int)) * CHAR_BIT - n));
    
    return x;
}

int bitcount(unsigned int x) {
	int noOfOnes = 0;
	while(x) {
		if(x & 1) {
			noOfOnes++;
		}
		x >>= 1;
	}

	return noOfOnes;
}

int bitcountVerTwo(unsigned int x) {
	int noOfOnes = 0;

	while(x) {
		noOfOnes++;
		x &= (x - 1);
	}

	return noOfOnes;
}

int changeToLowerVerTwo(const char c) {
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}
