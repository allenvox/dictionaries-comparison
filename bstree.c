#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

struct bstree *bstree_create(char *key, int value) {
  struct bstree *node;
  node = malloc(sizeof(*node));
  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

void bstree_add(struct bstree *tree, char *key, int value) {
  if (tree == NULL)
    return;
  struct bstree *parent, *node;
  while (tree != NULL) {
    parent = tree;
    if (key < tree->key)
      tree = tree->left;
    else if (key > tree->key)
      tree = tree->right;
    else
      return;
  }
  node = bstree_create(key, value);
  if (key < parent->key)
    parent->left = node;
  else
    parent->right = node;
}

struct bstree *bstree_lookup(struct bstree *tree, char *key) {
  while (tree != NULL) {
    if (key == tree->key)
      return tree;
    else if (key < tree->key)
      tree = tree->left;
    else
      tree = tree->right;
  }
  return tree;
}

struct bstree *bstree_min(struct bstree *tree) {
  if (tree == NULL)
    return NULL;
  while (tree->left != NULL)
    tree = tree->left;
  return tree;
}

struct bstree *bstree_max(struct bstree *tree) {
  if (tree == NULL)
    return NULL;

  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}

struct bstree *bstree_delete(struct bstree *tree, char *key) {
  if (tree == NULL)
    return tree;
  if (key < tree->key)
    tree->left = bstree_delete(tree->left, key);
  else if (key > tree->key)
    tree->right = bstree_delete(tree->right, key);
  else {
    if (tree->left == NULL) {
      struct bstree *temp = tree->right;
      free(tree);
      return temp;
    } else if (tree->right == NULL) {
      struct bstree *temp = tree->left;
      free(tree);
      return temp;
    }
    struct bstree *temp = bstree_min(tree->right);
    tree->key = temp->key;
    tree->right = bstree_delete(tree->right, temp->key);
  }
  return tree;
}