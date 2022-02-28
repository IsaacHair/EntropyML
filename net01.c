#include <stdlib.h>
#include <stdio.h>

struct node {
  struct node *parent[3];
  struct node *child[3];
  enum {NAND, XOR, TRANS, ROT, SCALE, IFELSE, REG0, REG1, REG2, REG3, ADD, SUB} type;
  int* weights; //include fuzzy memory as well
  int grid[256][256];
  int density0[1024][64];
  int density1[1024][64];
} network[100];

void link() {
  time_t t;
  char used[300]; //divide index by 3 with truncation to get corresponding node
  int idx;
  int node;
  int set;
  srand((unsigned) time(&t));
  
  for (node = 0; node < 100; node++) //ZZZ
}

void test() {
  
}

void main() {
  link();
  test();
  printf("done\n");
}
