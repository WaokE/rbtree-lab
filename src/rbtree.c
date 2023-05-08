#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  nil_node->key = NULL;
  // TODO: initialize struct if needed
  p->root = nil_node;
  p->nil = nil_node;
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *node_to_insert = (node_t *)calloc(1, sizeof(node_t));
  node_to_insert->color = RBTREE_RED;
  node_to_insert->key = key;
  
  // 노드를 삽입할 부모 탐색
  node_t *current = t->root;
  node_t *parent = t->nil;
  while (current != t->nil){
    parent = current;
    if (current->key == key){
      current = current->right;
    }
    else if (current->key > key){
      current = current->left; 
    }
    else if (current->key < key){
      current = current->right; 
    }
  }

  // 부모를 찾지 못했다면(루트노드 삽입시)
  if (parent == t->nil){
    t->root = node_to_insert;
  }
  // 찾았다면
  else{
    if (parent->key == node_to_insert->key){
      parent->right = node_to_insert;
      node_to_insert->parent = parent;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
    }
    else if (parent->key > node_to_insert->key){
      parent->left = node_to_insert;
      node_to_insert->parent = parent;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
    }
    else if (parent->key < node_to_insert->key){
      parent->right = node_to_insert;
      node_to_insert->parent = parent;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
    }
  }
}

void insert_fixup(node_t *node_inserted){
  // 삽입 노드 부모 색이 BLACK -> 문제 X
  if (node_inserted->parent->color = RBTREE_BLACK){
    return;
  }
  // 삽입 노드 부모 색이 RED -> 문제 발생
  else{
    // 삼촌 노드 찾기
    node_t *node_uncle;
    if (node_inserted->parent->parent->left == node_inserted->parent){
      node_uncle = node_inserted->parent->parent->right;
    }
    else{
      node_uncle = node_inserted->parent->parent->left;
    }
    // Case 1
    if (node_uncle->color == RBTREE_RED){
      node_inserted->parent->color = RBTREE_BLACK;
      node_uncle->color = RBTREE_BLACK;
      node_inserted->parent->parent->color = RBTREE_RED;
      insert_fixup(node_inserted->parent->parent);
    }
    // Case 2, 3
    else {
      node_t *grandparent = node_inserted->parent->parent;
      node_t *parent = node_inserted->parent;
      // Case 2-1 (오른쪽으로 꺾임)
      if (parent->left == node_inserted && grandparent->right == parent){
        // TODO: 부모 기준으로 오른쪽으로 회전 - Case 3로 만들어줌
      }
      // Case 2-2 (왼쪽으로 꺾임)
      else if (parent->left == node_inserted && grandparent->right == parent){
        // TODO: 부모 기준으로 왼쪽으로 회전 - Case 3 로 만들어줌
      }
      // Case 3
      color_t temp_color = parent->color;
      parent->color = grandparent->color;
      grandparent->color = temp_color;
      // TODO: 할아버지 기준으로 왼/오 회전
    }
  }

}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}

void check_tree(const rbtree *t) {
  // TODO: RB트리의 속성 몇번을 위반하는지 체크하고, 리턴해주는 함수
}