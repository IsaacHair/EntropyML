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
  int amountLeft;
  int idx;
  int node;
  int set;
  int tempChildAmount;
  int tempChildLocation;
  srand((unsigned) time(&t));
  
  for (idx = 0; idx < 300; idx++)
    used[idx] = 0;
  amountLeft = 300;
  for (node = 0; node < 100; node++)
    for (set = 0; set < 3; set++) {
      tempChildAmount = rand()%amountLeft;
      tempChildLocation = tempChildAmount; //abusing this to count
      for (idx = 0; idx < 300; idx++) {
        if (!used[tempChildLocation])
          tempChildLocation--;
        if (tempChildLocation < 0)
          break;
      }
      tempChildLocation = idx;
      network[node].child[set] = &network[tempChildLocation/3];
      network[tempChildLocation/3].parent[tempChildLocation%3] = &network[node];
      amountLeft--;
      used[tempChildLocation] = 1;
    }
}

void test() {
  
}

void main() {
  link();
  test();
  printf("done\n");
}
