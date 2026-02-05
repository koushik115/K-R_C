#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

enum boolean {NO, YES};
enum escapes {BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r'};
enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

int strLength(const char *string);
int isLeapYear(int year);
int asciiToInteger(const char *intString);
int changeToLower(const char c);
int hexToDec(const char *hex);
char *squeeze(char *s, char c);

int main(void) {

	/****************************** Exercise 2-1 ******************************/
	/*
	printf("Range of signed char is from %d to %d\n", (int)((-1 * pow(2, sizeof(char) * 8) / 2)), (int)(((1 * pow(2, sizeof(char) * 8)) / 2) - 1));
	printf("Range of unsigned char is from %d to %d\n", 0, (int)(((1 * pow(2, sizeof(char) * 8) - 1)))) ;
	
	printf("Range of signed short is from %d to %d\n", (int)((-1 * pow(2, sizeof(short) * 8) / 2)), (int)(((1 * pow(2, sizeof(short) * 8)) / 2) - 1));
	printf("Range of unsigned short is from %d to %d\n", 0, (int)(((1 * pow(2, sizeof(short) * 8) - 1)))) ;

	printf("Range of signed int is from %d to %d\n", (int)((-1 * pow(2, sizeof(int) * 8) / 2)), (int)(((1 * pow(2, sizeof(int) * 8)) / 2) - 1));
	printf("Range of unsigned int is from %d to %ld\n", 0, (long)(((1 * pow(2, sizeof(int) * 8) - 1)))) ;

	printf("Range of signed long is from %ld to %ld\n", (long)((-1 * pow(2, sizeof(long) * 8) / 2)), (long)(((1 * pow(2, sizeof(long) * 8)) / 2) - 1));
	printf("Range of unsigned long is from %d to %lu\n", 0, (unsigned long)(((1 * pow(2, sizeof(long) * 8) - 1)))) ;
	*/
	/*	
	char *exampleString = "The C Programming Language";
	printf("Size of the string is %d\n", strLength(exampleString));
	
	printf("%d\t%d", isLeapYear(2024), isLeapYear(2025));
	*/
	/******************************* Exercise 2-2 ********************************/
	/*
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
	*/
	/*
	printf("%d\n", asciiToInteger("12345"));
	*/
	/*
	printf("%c\n", changeToLower('F'));
	*/

	/********************************************* Exercise 2-3 *************************************/
	/*
	printf("%d\t%d\t%d\t%d\t%d\n", hexToDec("0x10fa"), hexToDec("0XBABE"), hexToDec("0xbabe"), hexToDec("0XFACE"), hexToDec("0xface"));
	*/

	char *stringExample = (char *)malloc(strlen("ExampleProgram") + 1);
	strcpy(stringExample, "ExampleProgram");
	printf("%s\n", squeeze(stringExample, 'x'));
	free(stringExample);

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

	while(*s != '\0') {
		if (*s == c) {
			s++; j++;
			continue;
		}
		*(s + i) = *(s + j);
		s++; i++; j++;
	}

	return s;
}
