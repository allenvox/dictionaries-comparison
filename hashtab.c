#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(char* key, hashtype type, int size){
    if(type == KR) {
        return KR_hash(key, size);
    } else {
        return FNV_hash(key, size);
    }
}

unsigned int FNV_hash(char *key, int size) {
  unsigned int h = 0x811c9dc5;
  while(*key) {
    h ^= (unsigned int)*key++;
    h *= 0x01000193;
  }
  return h % size;
}

unsigned int KR_hash(char *key, int size) {
  unsigned int h = 0, hash_mul = 31;
  while (*key)
    h = h * hash_mul + (unsigned int)*key++;
  return h % size;
}

void hashtab_init(listnode **hashtab, int size) {
  for (int i = 0; i < size; i++)
    hashtab[i] = NULL;
}

void hashtab_add(listnode **hashtab, char *key, int value, hashtype type, int size, int *collision) {
  int index = hash(key, type, size);
  listnode *node = malloc(sizeof(*node));
  if(node != NULL) { // malloc succeeded
    node->key = key;
    node->value = value;
    if(hashtab[index] != NULL) {
      *collision += 1;
      node->next = hashtab[index]->next;
      hashtab[index]->next = node;
    } else {
      node->next = hashtab[index];
      hashtab[index] = node;
    }
  } else {
    printf("Error while allocating memory\n");
  }
}

listnode *hashtab_lookup(listnode **hashtab, char *key, hashtype type, int size) {
  listnode *node;
  int index = hash(key, type, size);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key)) {
      return node;
    }
  }
  return NULL;
}

void hashtab_delete(listnode **hashtab, char *key, hashtype type, int size) {
  listnode *node, *prev = NULL;
  int index = hash(key, type, size);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key)) {
      if (prev == NULL)
        hashtab[index] = node->next;
      else
        prev->next = node->next;
      free(node);
      return;
    }
    prev = node;
  }
}

listnode *list_createnode(char *key, int value) {
  listnode *p = malloc(sizeof(*p));
  if (p != NULL) {
    p->key = key;
    p->value = value;
    p->next = NULL;
  }
  return p;
}

listnode *list_addfront(listnode *list, char *key, int value) {
  listnode *newnode = list_createnode(key, value);
  if (newnode != NULL) {
    newnode->next = list;
    return newnode;
  }
  return list;
}

listnode *list_lookup(listnode *list, char *key) {
  for (; list != NULL; list = list->next) {
    if (strcmp(list->key, key) == 0) {
      return list;
    }
  }
  return NULL; // if not found
}

listnode *list_delete(listnode *list, char *key) {
  listnode *p, *prev = NULL;
  for (p = list; p != NULL; p = p->next) {
    if (strcmp(p->key, key) == 0) {
      if (prev == NULL) {
        list = p->next; /* Удаляем голову */
      } else {
        prev->next = p->next; /* Есть элемент слева */
        free(p); /* Освобождаем память */
        return list; /* Указатель на новую голову */
      }
    }
    prev = p; /* Запоминаем предыдущий элемент */
  }
  return NULL; // not found
}