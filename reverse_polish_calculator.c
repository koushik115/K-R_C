#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE	100

int STACK[STACK_SIZE];
int stackp = -1;
void push(int c);
int pop(void);

int isNumOrOperator(char *str) {
		if((*str == '+' || *str == '-' || *str == '/' || *str == '*' || *str == '%') && *(str + 1) == '\0') {
			return 2;
		}

	while(*str != '\0') {
		if(!(*str >= '0' && *str <= '9'))
			return 0;
		str++;
	}

	return 1;
}

int main(int argc, char *argv[]) {
	int c, op1, op2, operand = 0;

	while(--argc > 0 && (c = isNumOrOperator((*++argv))) != 0) {
		if (c == 2) {
			if(*argv[0] == '+') {
				op1 = pop();
				op2 = pop();
				push(op1 + op2);
			} else if(*argv[0] == '-') {
				op2 = pop();
				push(pop() - op2);
			} else if(*argv[0] == '/') {
				op2 = pop();
				if(op2 != 0) {
					push(pop() / op2);
				} else {
					exit(1);
				}
			} else if(*argv[0] == '*') {
				op1 = pop();
				op2 = pop();
				push(op1 * op2);
			} else if(*argv[0] == '%') {
				op2 = pop();
				if(op2 != 0) {
					push(pop() % op2);
				} else {
					exit(1);
				}
			}
		} else if(c == 1) {
			while(*argv[0] != '\0') {
				operand = operand * 10 + (*argv[0] - '0');
				argv[0]++;
			}

			push(operand);
			operand = 0;
		}
	}
	
	printf("%d\n", pop());
	
	return 0;
}

void push(int c) {
    if(stackp < STACK_SIZE - 1)
        STACK[++stackp] = c;
}

int pop(void) {
    if(stackp > -1)
        return STACK[stackp--];
    else
        exit(1);
}

