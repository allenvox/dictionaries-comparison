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

void experiment1() {
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
    tree = bstree_create(words[0], 0);

    for(int m = 0; m < size; m++) { // filling structures with words
      bstree_add(tree, words[m], m);
    }

    double treeTime = wtime();
    treeNode = bstree_lookup(tree, words[getRand(0, size-1)]);
    treeTime = wtime() - treeTime;

    if(treeNode != NULL) {
      printf("[tree] n: %d t: %.6lf\n", size, treeTime);
    }
  }

  printf("\n");
  for(int size = 10000; size <= 200000; size += 10000) {
    listnode *hashNode, *hashtab[size];
    hashtab_init(hashtab, size);
    int col = 0;
    for(int m = 0; m < size; m++) { // filling KR-hashtab with words
      hashtab_add(hashtab, words[m], m, KR, size, &col);
    }

    double hashTime = wtime();
    hashNode = hashtab_lookup(hashtab, words[getRand(0, size-1)], KR, size);
    hashTime = wtime() - hashTime;

    if(hashNode != NULL) {
      printf("[hash] n: %d t: %.6lf\n", size, hashTime);
    }
  }
}

void experiment4(){
  //average case
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
    tree = bstree_create(words[0], 0);

    for(int m = 1; m < size/2; m++) { // std - ascending
      bstree_add(tree, words[m], m);
    }
    bstree_add(tree, words[size/2], 0);
    for(int m = size/2 +1; m < size-1; m++) {
      bstree_add(tree, words[m], m);
    }

    double treeTime = wtime();
    treeNode = bstree_min(tree);
    treeTime = wtime() - treeTime;

    if(treeNode != NULL) {
      printf("[tree min avg] n: %d t: %.6lf\n", size, treeTime);
    }
  }

  for(int size = 10000; size <= 200000; size += 10000) {
    struct bstree *treeNode, *tree;
    tree = bstree_create(words[0], 0);

    for(int m = size-1; m >= 0; m--) { // descending
      bstree_add(tree, words[m], m);
    }

    double treeTime = wtime();
    treeNode = bstree_min(tree);
    treeTime = wtime() - treeTime;

    if(treeNode != NULL) {
      printf("[tree min worst] n: %d t: %.6lf\n", size, treeTime);
    }
  }
}

void experiment6(){
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
    listnode *KR_hashtab[size];
    listnode *FNV_hashtab[size];
    hashtab_init(KR_hashtab, size);
    hashtab_init(FNV_hashtab, size);
    int KR_collisions = 0, FNV_collisions = 0;
    for(int i = 0; i < size; i++) {
      hashtab_add(KR_hashtab, words[i], i, KR, size, &KR_collisions);
      hashtab_add(FNV_hashtab, words[i], i, FNV, size, &FNV_collisions);
    }
    double t = wtime();
    listnode *node = hashtab_lookup(KR_hashtab, words[getRand(0, size-1)], KR, size);
    t = wtime() - t;
    printf("[KR]  n: %d t: %.6f collisions: %d\n", size, t, KR_collisions);
    t = wtime();
    node = hashtab_lookup(FNV_hashtab, words[getRand(0, size-1)], FNV, size);
    t = wtime() - t;
    printf("[FNV] n: %d t: %.6f collisions: %d\n", size, t, FNV_collisions);
    
    if(size == 200000) {
      for(int i = 0; i < size; i++) {
        listnode *nodee = FNV_hashtab[i];
        if(nodee != NULL) {
          printf("%d. key: %s value: %d\n", i, nodee->key, nodee->value);
          listnode *nodeee = nodee->next;
          if(nodeee != NULL) {
            printf("\tnext in it: key: %s value: %d\n", nodeee->key, nodeee->value);
            listnode *nodeeee = nodeee->next;
            if(nodeeee != NULL) {
              printf("\t\tnext in it: key: %s value: %d\n", nodeeee->key, nodeeee->value);
              listnode *nodeeeee = nodeeee->next;
              if(nodeeeee != NULL) {
                printf("\t\t\tnext in it: key: %s value: %d\n", nodeeeee->key, nodeeeee->value);
              }
            }
          }
        }
      }
    }
    
    listnode *finding = hashtab_lookup(FNV_hashtab, "bbfbadf", FNV, size);
    if(finding != NULL) {
      printf("Found the node that is in linked list!\n");
    }
  }
}

int main() {
  experiment6();
  return 0;
}