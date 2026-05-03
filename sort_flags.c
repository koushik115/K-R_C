#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void Qsort(void *lineptr[], int left, int right, int (*cmp)(void *, void *));
int mycmp(char *s1, char *s2);
int numcmp(char *s1, char *s2);

int numeric = 0, reverse = 0, fold = 0, directory = 0;

int main(int argc, char **argv) {
	int nlines;

	if (argc > 1) {
		while (*++argv != NULL) {
			if (strcmp(*argv, "-n") == 0)
				numeric = 1;
			else if (strcmp(*argv, "-r") == 0)
				reverse = 1;
			else if (strcmp(*argv, "-f") == 0)
				fold = 1;
			else if (strcmp(*argv, "-d") == 0)
				directory = 1;
		}
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		Qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))mycmp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort!\n");
		return 1;
	}
	return 0;
}

#define MAXLEN 1000

int getLine(char *line, int maxline);
char *alloc(int n);

int readlines(char *lineptr[], int maxline) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0) {
		if (nlines >= maxline || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}

	return nlines;
}

#define ALLOCSIZE 1000
char allocbuffer[ALLOCSIZE];
char *allocp = allocbuffer;

int getLine(char *line, int maxline) {
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n')
		line[i++] = c;

	line[i] = '\0';

	return i;
}

char *alloc(int n) {
	if ((allocbuffer + ALLOCSIZE - allocp) >= n) {
		allocp += n;
		return allocp - n;
	} else
		return NULL;
}

void writelines(char *lineptr[], int nlines) {
	for (int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void Qsort(void *v[], int left, int right, int (*cmp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if ((*cmp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}

	swap(v, left, last);
	Qsort(v, left, last - 1, cmp);
	Qsort(v, last + 1, right, cmp);
}
/*
int mycmp(char *s1, char *s2) {
  int result = 0;
  char c1, c2;
  if (numeric) {
    result = numcmp(s1, s2);
  } else if (fold) {
    while (*s1 != '\0' && *s2 != '\0') {
      c1 = tolower(*s1);
      c2 = tolower(*s2);
      result = (c1 > c2) ? 1 : (c1 < c2) ? -1 : 0;
      if (result != 0)
        break;
      s1++;
      s2++;
    }

    if (!result) {
      if (*s1 != '\0')
        result = 1;
      else if (*s2 != '\0')
        result = -1;
      else
        result = 0;
    }
  } else {
    result = strcmp(s1, s2);
  }

  if (reverse)
    return -result;
  else
    return result;
}
*/
// int mycmp(char *s1, char *s2) {
// 	int result = 0;
// 	char c1 = 0, c2 = 0;

// 	if (numeric) {
// 		result = numcmp(s1, s2);
// 	} else {
// 		if (directory) {
// 			while (*s1 != '\0' && *s2 != '\0') {
// 				while (*s1 != '\0' && !isalnum(*s1) && *s1 != ' ')
// 					s1++;

// 				while (*s2 != '\0' && !isalnum(*s2) && *s2 != ' ')
// 					s2++;

// 				if(fold)
// 					c1 = *s1 == '\0' ? *s1 : tolower(*s1);
// 				else
// 					c1 = *s1;

// 				if(fold)
// 					c2 = *s2 == '\0' ? *s2 : tolower(*s2);
// 				else
// 					c2 = *s2;


// 				result = (c1 > c2) ? 1 : (c1 < c2) ? -1 : 0;
// 				if (result != 0)
// 					return result;

// 				if (*s1 != '\0')
// 					s1++;
// 				if (*s2 != '\0')
// 					s2++;
// 			}

// 			if (!result) {
// 				if (*s1 != '\0') {
// 					while (*s1 != '\0' && !isalnum(*s1) && *s1 != ' ')
// 						s1++;

// 					if(*s1 != '\0')
// 						result = 1;
// 					else
// 						result = 0;
// 				} else if (*s2 != '\0') {
// 					while (*s2 != '\0' && !isalnum(*s2) && *s2 != ' ')
// 						s2++;

// 					if(*s2 != '\0')
// 						result = -1;
// 					else
// 						result = 0;
// 				} else
// 					result = 0;
// 			}
// 		} else if (fold) {
// 			while (*s1 != '\0' && *s2 != '\0') {
// 				c1 = tolower(*s1);
// 				c2 = tolower(*s2);
// 				result = (c1 > c2) ? 1 : (c1 < c2) ? -1 : 0;
// 				if (result != 0)
// 					break;
// 				s1++;
// 				s2++;
// 			}

// 			if (!result) {
// 				if (*s1 != '\0')
// 					result = 1;
// 				else if (*s2 != '\0')
// 					result = -1;
// 				else
// 					result = 0;
// 			}
// 		} else {
// 			result = strcmp(s1, s2);
// 		}

// 		if (reverse)
// 			return -result;
// 		else
// 			return result;
// 	}
// }

int mycmp(char *s1, char *s2) {
	int result = 0;
	char c1 = 0, c2 = 0;

	if (numeric) {
		result = numcmp(s1, s2);
	} else {
		while(1) {
			if(directory) {
				while (*s1 != '\0' && !isalnum(*s1) && *s1 != ' ')
					s1++;

				while (*s2 != '\0' && !isalnum(*s2) && *s2 != ' ')
					s2++;
			}

			c1 = *s1;
			c2 = *s2;

			if(fold) {
				c1 = tolower(c1);
				c2 = tolower(c2);
			}

			if(c1 != c2) {
				result = c1 - c2;
				if (reverse)
					return -result;
				else
					return result;
			}

			if(c1 == '\0')
				return 0;

			s1++;
			s2++;
		}
	}

	if (reverse)
		return -result;
	else
		return result;
}


int numcmp(char *s1, char *s2) {
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
