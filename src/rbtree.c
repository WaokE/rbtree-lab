#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree* new_rbtree(void) {
	rbtree* p = (rbtree*)calloc(1, sizeof(rbtree));
	// TODO: initialize struct if needed
	p->root = 0;
	p->nil = 0;
	return p;
}

void delete_rbtree(rbtree* t) {
	// TODO: reclaim the tree nodes's memory: RBtree 구조체가 차지했던 메모리 반환
	delete_one(t, t->root);
	free(t->nil);
	free(t);
}

void delete_one(rbtree* t, node_t* cur) {
	if (cur != t->nil) {
		delete_one(t, cur->left);
		delete_one(t, cur->right);
		free(cur);
	}
}

void rotate_left(rbtree *t, node_t *x){
	node_t *y = x->right;
	x->right = y->left; //y의 왼쪽의 서버트리를 x의 오른쪽 서버트리로 옮김
	if (y->left != t->nil){
		y->left->parent = x;
	}
	y -> parent = x ->parent;
	if (x-> parent == t->nil){ //x가 루트노드라면
		t->root = y;
	}
	else if (x == x->parent->left){ //x가 왼쪽 자식일 경우
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rotate_right(rbtree *t, node_t *x){
	node_t *y = x->left;
	x->left = y->right; //y의 오른쪽 서버트리를 x의 왼쪽 서버트리로 옮김
	if (y->right != t->nil){
		y->right->parent = x;
	}
	y -> parent = x ->parent;
	if (x-> parent == t->nil){ //x가 루트노드라면
		t->root = y;
	}
	else if (x == x->parent->right){
		x->parent->right = y;
	}
	else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
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

  // 부모를 찾지 못했다면
  if (parent == t->nil){
    t->root = node_to_insert;
  }
  // 찾았다면
  else{
    if (parent->key == node_to_insert->key){
      parent->right = node_to_insert;
    }
    else if (parent->key > node_to_insert->key){
      parent->left = node_to_insert;
    }
    else if (parent->key < node_to_insert->key){
      parent->right = node_to_insert;
    }
  }
}

node_t* rbtree_find(const rbtree* t, const key_t key) {
	// TODO: implement find
	//  RB tree내에 해당 key가 있는지 탐색하여 있으면 해당 노드 반환.
	node_t *tmp = t->root;
	if (tmp != NULL){
		while (tmp != NULL & tmp -> key != key){
			if (tmp->key > key){ //tmp가 가리키는 key값이 찾아야 할 key값보다 크면, tmp를 줄여서 key값에 가깝게해야 함.
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}
		}
		return tmp; //tmp->key == key라면 바로 tmp 반환
	} return NULL;
}

node_t* rbtree_min(const rbtree* t) {
	// TODO: implement find: tree의 min key를 가지는 노드반환
	node_t* tmp = t->root;
	if (tmp != NULL) {
		while (tmp->left != NULL) {
			tmp = tmp->left;
		}
	}
	return tmp;
}

node_t* rbtree_max(const rbtree* t) {
	// TODO: implement find: tree의 max key를 가지는 노드반환
	node_t* tmp = t->root;
	if (tmp != NULL) {
		while (tmp->right != NULL) {
			tmp = tmp->right;
		}
	}
	return tmp;
}

int rbtree_erase(rbtree* t, node_t* p) {
	// TODO: implement erase: 특정 노드 삭제 작업
	return 0;
}

int rbtree_to_array(const rbtree* t, key_t* arr, const size_t n) {
	// TODO: implement to_array
	return 0;
}