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
  char used[100];
  int counter;
  int choice0;
  int choice1;
  int pos0;
  int pos1;
  int remaining;
  int set;
  srand((unsigned) time(&t));
  
  for (set = 0; set < 3; set++) {
    for (counter = 0; counter < 100; counter++)
      used[counter] = 0;
    for (remaining = 100; remaining > 0;) {
      choice0 = rand() % remaining;
      for (counter = choice0+1, pos0 = 0; 1; pos0++) {
        if (!used[pos0])
          counter--;
        if (!counter)
          break;
      }
      used[pos0] = 1;
      remaining--;
      choice1 = rand() % remaining;
      for (counter = choice1+1, pos1 = 0; 1; pos1++) {
        if (!used[pos1])
          counter--;
        if (!counter)
          break;
      }
      used[pos1] = 1;
      remaining--;

      network[pos0].parent[set] = &network[pos1];
      network[pos1].child[set] = &network[pos0];
      
    }
  }
}

void test() {
  int i, set;
  for (set = 0; set < 3; set++)
    for (i = 0; i < 100; i++)
      if (&(network[i]) != (network[i].parent[set])->child[set])
        printf("link failure for parent of set %d index %d\n", set, i);
  printf("test complete\n");
}

void main() {
  link();
  test();
}
