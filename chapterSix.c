#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int getword(char *word, int lim);
int binsearch(char *word, struct key *keytab, int n);

struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};

struct key {
  char *word;
  int count
} keytab[] = {{"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
              {"const", 0},    {"continue", 0}, {"default", 0},  {"do", 0},
              {"double", 0},   {"else", 0},     {"enum", 0},     {"extern", 0},
              {"float", 0},    {"for", 0},      {"goto", 0},     {"if", 0},
              {"int", 0},      {"long", 0},     {"register", 0}, {"return", 0},
              {"short", 0},    {"signed", 0},   {"sizeof", 0},   {"static", 0},
              {"struct", 0},   {"switch", 0},   {"typedef", 0},  {"union", 0},
              {"unsigned", 0}, {"void", 0},     {"volatile", 0}, {"while", 0}};

int main(void) {
  /*
  struct rect screen;
  struct point middle;
  struct point p1, p2, sum;
  struct rect canon;

  struct point makepoint(int x, int y);
  struct point addpoint(struct point p1, struct point p2);
  int ptinrect(struct point p, struct rect r);
  struct rect canonrect(struct rect r);

  screen.pt1 = makepoint(0, 0);
  screen.pt2 = makepoint(10, 10);

  middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
                     (screen.pt1.y + screen.pt2.y) / 2);

  printf("Middle Point: (%d, %d)\n", middle.x, middle.y);
  */

  /* addpoint example */
  /*
p1 = makepoint(2, 3);
p2 = makepoint(4, 5);
sum = addpoint(p1, p2);

printf("Sum of points: (%d, %d)\n", sum.x, sum.y);
*/
  /* ptinrect example */
  /*
if (ptinrect(middle, screen))
printf("Middle point is inside the rectangle\n");
else
printf("Middle point is outside the rectangle\n");
*/
  /* canonrect example */
  /*
  canon = canonrect(screen);

  printf("Canonical rectangle:\n");
  printf("pt1: (%d, %d)\n", canon.pt1.x, canon.pt1.y);
  printf("pt2: (%d, %d)\n", canon.pt2.x, canon.pt2.y);
  */

  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
        keytab[n].count++;
      }
    }
  }

  for (n = 0; n < NKEYS; n++) {
    if (keytab[n].count > 0) {
      printf("%4d %s\n", keytab[n].count, keytab[n].word);
    }
  }

  return 0;
}

struct point makepoint(int x, int y) {
  struct point temp;

  temp.x = x;
  temp.y = y;

  return temp;
}

struct point addpoint(struct point p1, struct point p2) {
  p1.x += p2.x;
  p1.y += p2.y;

  return p1;
}

int ptinrect(struct point p, struct rect r) {
  return (p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y);
}

struct rect canonrect(struct rect r) {
  struct rect temp;

  temp.pt1.x = min(r.pt1.x, r.pt2.x);
  temp.pt1.y = min(r.pt1.y, r.pt2.y);
  temp.pt2.x = max(r.pt1.x, r.pt2.x);
  temp.pt2.y = min(r.pt1.y, r.pt2.y);

  return temp;
}

int binsearch(char *word, struct key *keytab, int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, ketab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }

  return -1;
}

/* TODO: Implement the getword here */
