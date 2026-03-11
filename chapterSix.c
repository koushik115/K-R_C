#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};

int main(void) {
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

  /* addpoint example */
  p1 = makepoint(2, 3);
  p2 = makepoint(4, 5);
  sum = addpoint(p1, p2);

  printf("Sum of points: (%d, %d)\n", sum.x, sum.y);

  /* ptinrect example */
  if (ptinrect(middle, screen))
    printf("Middle point is inside the rectangle\n");
  else
    printf("Middle point is outside the rectangle\n");

  /* canonrect example */
  canon = canonrect(screen);

  printf("Canonical rectangle:\n");
  printf("pt1: (%d, %d)\n", canon.pt1.x, canon.pt1.y);
  printf("pt2: (%d, %d)\n", canon.pt2.x, canon.pt2.y);

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
