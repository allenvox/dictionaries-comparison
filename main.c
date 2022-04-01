#include "bstree.h"
#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int getRand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max + 1 - min) + min;
}

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main() {
  // filling the words array
  char words[200000][8];
  FILE *inp;
  inp = fopen("words.txt", "r");
  int i = 0;
  while (1) {
    char r = (char)fgetc(inp);
    int k = 0;
    while (r != '\n' && !feof(inp)) {
      words[i][k++] = r;
      r = (char)fgetc(inp);
    }
    words[i][k] = 0;
    if (feof(inp)) {
      break;
    }
    i++;
  }

  for(int size = 10000; size <= 200000; size += 10000) {
    struct bstree *treeNode, *tree;
    tree = bstree_create(0, words[0]);

    for(int m = 0; m < size; m++) { // filling structures with words
      bstree_add(tree, m, words[m]);
    }

    double treeTime = wtime();
    treeNode = bstree_lookup(tree, getRand(0, size-1));
    treeTime = wtime() - treeTime;

    if(treeNode != NULL) {
      printf("[tree] n: %d t: %.6lf\n", size, treeTime);
    }
  }

  printf("\n");
  for(int size = 10000; size <= 200000; size += 10000) {
    struct listnode *hashNode, *hashtab[size];
    hashtab_init(hashtab);

    for(int m = 0; m < size; m++) { // filling hashtab with words
      hashtab_add(hashtab, words[m], m);
    }

    double hashTime = wtime();
    hashNode = hashtab_lookup(hashtab, words[getRand(0, size-1)]);
    hashTime = wtime() - hashTime;

    if(hashNode != NULL) {
      printf("[hash] n: %d t: %.6lf\n", size, hashTime);
    }
  }
  return 0;
}