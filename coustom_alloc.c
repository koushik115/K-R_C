#include <stdio.h>

#define ALLOCSIZE	10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
	if((allocbuf + ALLOCSIZE - allocp) >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return NULL;
	}
}

void afree(char *p)  {
	if(p >= allocbuf && p <= allocbuf + ALLOCSIZE)
		allocp = p;
}

int main(void) {
	char *buffer = alloc(10);
	
	for(int i = 0; i < 10; i++)
		buffer[i] = i;

	afree(buffer);

	return 0;
}
