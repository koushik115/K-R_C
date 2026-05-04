#include <stdio.h>

long int fact(int n) {
	if(n == 0)
		return 1;

	return n * fact(n -1);
}

int summation(int n) {
	if(n == 0)
		return 0;

	return n + summation(n - 1);
}

void display1(int n) {
	if(n == 0)
		return;

	printf("%d ", n);
	display1(n - 1);
}

void display2(int n) {
	if(n == 0) 
		return;

	display2(n - 1);
	printf("%d ", n);
}

int rseries(int n) {
	int sum;
	if(n == 0)
		return 0;
	return n + rseries(n - 1);
	printf("%d + ", n);
}

int main(void) {
/*
	printf("%ld ", fact(3));
	printf("\n");

	printf("%d", summation(4));
	printf("\n");

	display1(5);
	printf("\n");

	display2(5);
	printf("\n");
*/
	printf("\b\b = %d\n", rseries(5));
	return 0;
}

