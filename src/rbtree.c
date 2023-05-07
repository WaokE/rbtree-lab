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


  // TODO: 아래 부분 2번속성 위배 처리부로 변경할것.
  // else{
  //   t->root = node_to_insert;
  //   node_to_insert->color = RBTREE_BLACK;
  // }
  // return t->root;
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

node_t *rbtree_where_to_insert(const rbtree *t, const key_t key) {
  // TODO: 노드 삽입할 위치를 찾는 함수
  node_t *current = t->root;
  // current가 NIL노드일 때 까지
  while (current->key != NULL){
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
  // 현재 주소를 리턴
  return current;
}