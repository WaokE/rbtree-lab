#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  // TODO: initialize struct if needed
  p->root = nil_node;
  p->nil = nil_node;
  return p;
}

void rotate_left(rbtree *t, node_t *x){
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (t->root == x){
    t->root = y;
  }
  // x가 부모의 왼쪽이면
  else if (x == x->parent->left){
    x->parent->left = y;
  }
  // x가 부모의 오른쪽이면
  else{
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rotate_right(rbtree *t, node_t *y){
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil){
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (t->root == y){
    t->root = x;
  }
  // y가 부모의 왼쪽이면
  else if (y == y->parent->left){
    y->parent->left = x;
  }
  // y가 부모의 오른쪽이면
  else{
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t* rbtree_insert_fixup(rbtree* t, node_t *node_to_insert){
	node_t *grandparent = node_to_insert->parent->parent;
	while (node_to_insert->parent->color == RBTREE_RED){
		//case1. 부모, 삼촌 ==RED -> 부모삼촌 모두 black으로 바꾸고, 할아버지는 red.
		if (node_to_insert->parent == grandparent->left){
			node_t *uncle = grandparent->right;
			if (uncle->color == RBTREE_RED){
				node_to_insert->parent->color == RBTREE_BLACK;
				uncle->color == RBTREE_BLACK;
				grandparent->color == RBTREE_RED;
				node_to_insert = grandparent; // while문으로 다시 할아버지 확인
			} else { // case2, case3. 부모는 red인데 삼촌이 black인 경우
				//case2.
				if (node_to_insert == node_to_insert->parent->right){
					node_to_insert = node_to_insert->parent; 
					rotate_left(t, node_to_insert); //부모를 기준으로 왼쪽으로 회전
				}
				grandparent->color = RBTREE_RED;
				node_to_insert -> parent -> color = RBTREE_BLACK;
				rotate_right(t, grandparent);
			}
		}else{
			node_t *uncle = grandparent->left;
			if (uncle->color == RBTREE_RED){
				node_to_insert->parent->color = RBTREE_BLACK;
				uncle->color = RBTREE_BLACK;
				grandparent->color = RBTREE_RED;
				node_to_insert = grandparent;
			} else {
				if (node_to_insert == node_to_insert->parent->left){
					node_to_insert = node_to_insert->parent;
					rotate_left(t, node_to_insert);
				}
				grandparent->color = RBTREE_RED;
				node_to_insert->parent->color = RBTREE_BLACK;
				rotate_left(t, grandparent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;
	return t->root;
}

// void insert_fixup(rbtree *t, node_t *node_inserted){
//   node_t *grandparent = node_inserted->parent->parent;
//   node_t *parent = node_inserted->parent;
//   // 삽입 노드 부모 색이 BLACK -> 문제 X
//   if (parent->color == RBTREE_BLACK){
//     return;
//   }
//   // 삽입 노드 부모 색이 RED -> 문제 발생
//   else{
//     // 삼촌 노드 찾기
//     node_t *node_uncle;
//     if (grandparent->left == parent){
//       node_uncle = grandparent->right;
//     }
//     else{
//       node_uncle = grandparent->left;
//     }
//     // Case 1
//     if (node_uncle->color == RBTREE_RED){
//       parent->color = RBTREE_BLACK;
//       node_uncle->color = RBTREE_BLACK;
//       grandparent->color = RBTREE_RED;
//       insert_fixup(t, grandparent);
//     }
//     // Case 2, 3
//     else {
//       // Case 2-1 (오른쪽으로 꺾임)
//       if (parent->left == node_inserted && grandparent->right == parent){
//         // TODO: 부모 기준으로 오른쪽으로 회전 - Case 3로 만들어줌
//         rotate_right(t, parent);
//       }
//       // Case 2-2 (왼쪽으로 꺾임)
//       else if (parent->right == node_inserted && grandparent->left == parent){
//         // TODO: 부모 기준으로 왼쪽으로 회전 - Case 3 로 만들어줌
//         rotate_left(t, parent);
//       }
//       // Case 3
//       color_t temp_color = parent->color;
//       parent->color = grandparent->color;
//       grandparent->color = temp_color;
//       if (grandparent->left == parent){
//         rotate_right(t, grandparent);
//       }
//       else{
//         rotate_left(t, grandparent);
//       }
//     }
//   }
// }

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  // 삽입할 노드 선언
  node_t *node_to_insert = (node_t *)calloc(1, sizeof(node_t));
  node_to_insert->color = RBTREE_RED;
  node_to_insert->key = key;
  
  // 노드를 삽입할 부모 탐색
  node_t *current = t->root;
  node_t *parent_location = t->nil;
  while (current != t->nil){
    parent_location = current;
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
  if (parent_location == t->nil){
    t->root = node_to_insert;
    node_to_insert->left = t->nil;
    node_to_insert->right = t->nil;
    node_to_insert->parent = t->nil;
    // 2번 속성 만족을 위해 루트 BLACK으로
    node_to_insert->color = RBTREE_BLACK;
  }
  // 찾았다면
  else{
    if (parent_location->key == node_to_insert->key){
      parent_location->right = node_to_insert;
      node_to_insert->parent = parent_location;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
      rbtree_insert_fixup(t, node_to_insert);
    }
    else if (parent_location->key > node_to_insert->key){
      parent_location->left = node_to_insert;
      node_to_insert->parent = parent_location;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
      rbtree_insert_fixup(t, node_to_insert);
    }
    else if (parent_location->key < node_to_insert->key){
      parent_location->right = node_to_insert;
      node_to_insert->parent = parent_location;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
      rbtree_insert_fixup(t, node_to_insert);
    }
  }
  return node_to_insert;
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