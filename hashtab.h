#pragma once

typedef struct listnode {
  char *key;
  int value;
  struct listnode *next;
} listnode;

typedef enum hashtype { KR, FNV } hashtype;

unsigned int hash(char *key, hashtype type, int size);
unsigned int FNV_hash(char *key, int size);
unsigned int KR_hash(char *key, int size);
void hashtab_init(listnode **hashtab, int size);
void hashtab_add(listnode **hashtab, char *key, int value, hashtype type, int size, int *collision);
listnode *hashtab_lookup(listnode **hashtab, char *key, hashtype type, int size);
void hashtab_delete(listnode **hashtab, char *key, hashtype type, int size);
listnode *list_createnode(char *key, int value);
listnode *list_addfront(listnode *list, char *key, int value);
listnode *list_lookup(listnode *list, char *key);
listnode *list_delete(listnode *list, char *key);