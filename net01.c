#include <stdlib.h>
#include <stdio.h>

struct node {
  struct node *parent[3];
  struct node *child[3];
  enum {NAND, XOR, TRANS, ROT, SCALE, IFELSE, REG0, REG1, REG2, REG3, ADD, SUB} type; //12 types
  float weights[10]; //include fuzzy memory as well
  int grid[256][256];
  int density0[1024][64];
  int density1[1024][64];
} network[100];

void link() {
  char used[300]; //divide index by 3 with truncation to get corresponding node
  int amountLeft;
  int idx;
  int node;
  int set;
  int tempChildDrift;
  int tempChildLocation;
  
  for (idx = 0; idx < 300; idx++)
    used[idx] = 0;
  amountLeft = 300;
  for (node = 0; node < 100; node++)
    for (set = 0; set < 3; set++) {
      tempChildDrift = rand()%amountLeft;
      tempChildLocation = tempChildDrift; //abusing this to count
      for (idx = 0; idx < 300; idx++) {
        if (!used[idx])
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
  int node;
  int set;
  int errors;
  errors = 0;
  for (node = 0; node < 100; node++)
    for (set = 0; set < 3; set++) {
      printf("%d.%d: %d goes to %d which is from %d or %d or %d\n", node, set, &network[node], network[node].child[set], network[node].child[set]->parent[0], network[node].child[set]->parent[1], network[node].child[set]->parent[2]);
      if ((&network[node] != network[node].child[set]->parent[0]) && (&network[node] != network[node].child[set]->parent[1]) && (&network[node] != network[node].child[set]->parent[2]))
        errors++;
    }
  printf("errors=%d\n", errors);
}

void assign() {
  int node;
  int i, j;
  for (node = 0; node < 100; node++) {
    network[node].type = rand()%12;
    for (i = 0; i < 10; i++)
      network[node].weights[i] = (float) rand() / 65536;
    for (i = 0; i < 256; i++)
      for (j = 0; j < 256; j++)
        network[node].grid[i][j] = rand();
  }
}

void tick(int startgrid[256][256]) {
  int node;
  for (node = 0; node < 100; node++)
    1; //add a switch for the different node types and each function for those types
}

void main() {
  int startgrid[256][256]; //this is just a sample input image
  int i, j;
  time_t t;
  srand((unsigned) time(&t));
  for (i = 0; i < 256; i++)
    for (j = 0; j < 256; j++)
      startgrid[i][j] = rand();
  
  link();
  test();
  assign();
  tick(startgrid);
  printf("done\n");
}
