#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
key_t inorder_count;

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  // TODO: initialize struct if needed
  p->root = p->nil;
  
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

void insert_fixup(rbtree *t, node_t *node_inserted){
  node_t *grandparent = node_inserted->parent->parent;
  node_t *parent = node_inserted->parent;
  // 삽입 노드 부모 색이 BLACK -> 문제 X
  if (parent->color == RBTREE_BLACK){
    return;
  }
  // 삽입 노드 부모 색이 RED -> 문제 발생
  else{
    // 삼촌 노드 찾기
    node_t *node_uncle;
    if (grandparent->left == parent){
      node_uncle = grandparent->right;
    }
    else{
      node_uncle = grandparent->left;
    }
    // Case 1
    if (node_uncle->color == RBTREE_RED){
      parent->color = RBTREE_BLACK;
      node_uncle->color = RBTREE_BLACK;
      grandparent->color = RBTREE_RED;
      if (t->root == grandparent){
        t->root->color = RBTREE_BLACK;
      }
      insert_fixup(t, grandparent);
    }
    // Case 2, 3
    else {
      // Case 2-1 (오른쪽으로 꺾임)
      if (parent->left == node_inserted && grandparent->right == parent){
        // TODO: 부모 기준으로 오른쪽으로 회전 - Case 3로 만들어줌
        rotate_right(t, parent);
        parent = node_inserted;
      }
      // Case 2-2 (왼쪽으로 꺾임)
      else if (parent->right == node_inserted && grandparent->left == parent){
        // TODO: 부모 기준으로 왼쪽으로 회전 - Case 3 로 만들어줌
        rotate_left(t, parent);
        parent = node_inserted;
      }
      // Case 3
      color_t temp_color = parent->color;
      parent->color = grandparent->color;
      grandparent->color = temp_color;
      if (grandparent->left == parent){
        rotate_right(t, grandparent);
      }
      else{
        rotate_left(t, grandparent);
      }
    }
  }
}

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
    node_to_insert->parent = parent_location;
    // 2번 속성 만족을 위해 루트 BLACK으로
    node_to_insert->color = RBTREE_BLACK;
  }

  // 찾았다면
  else{
    if (parent_location->key == node_to_insert->key){
      parent_location->right = node_to_insert;
    }
    else if (parent_location->key > node_to_insert->key){
      parent_location->left = node_to_insert;
    }
    else if (parent_location->key < node_to_insert->key){
      parent_location->right = node_to_insert;
    }
      node_to_insert->parent = parent_location;
      node_to_insert->right = t->nil;
      node_to_insert->left = t->nil;
      insert_fixup(t, node_to_insert);
  }
  return node_to_insert;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *current = t->root;
  while (current != t->nil){
    if (current->key == key){
      return current;
    }
    else if (current->key < key){
      current = current->right;
    }
    else if (current->key > key){
      current = current->left;
    }
  }
  return NULL;
}

node_t *erase_min(node_t *n, node_t *nil){
  node_t *min = n;
  while (n != nil)               
  {
    min = n;
    n = n->left; 
  }
  return min;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *min = erase_min(t->root, t->nil);
  return min;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement fin
  node_t *current = t->root;
  node_t *max = t->root;
  while (current != t->nil){
    max = current;
    current = current->right;
  }
  return max;
}

// void rb_transplant(rbtree *T,node_t *u, node_t *v){
//   if (u->parent == T->nil){
//     T->root = v;
//   }
//   else if (u == u->parent->left){
//     u->parent->left = v;
//   }
//   else{
//     u->parent->right = v;
//   }
//   v->parent = u->parent;
// }

// void delete_fixup(rbtree *t, node_t *x){
//   while (x != t->root && x->color == RBTREE_BLACK){
//     if (x == x->parent->left){
//       node_t *w = x->parent->right;
//       // Case 1
//       if (w->color == RBTREE_RED){
//         w->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         rotate_left(t, x->parent);
//         w = x->parent->right;
//       }
//       // Case 2
//       if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
//         w->color = RBTREE_RED;
//         x = x->parent;
//       }
//       // Case 3
//       else{ 
//         if (w->right->color == RBTREE_BLACK) {
//         w->left->color = RBTREE_BLACK;
//         w->color = RBTREE_RED;
//         rotate_right(t, w);
//         w = x->parent->right;
//       }
//       // Case 4
//       w->color = x->parent->color;
//       x->parent->color = RBTREE_BLACK;
//       w->right->color = RBTREE_BLACK;
//       rotate_left(t, x->parent);
//       x = t->root;
//     }
//     }
//     else{
//       node_t *w = x->parent->left;
//       // Case 1
//       if (w->color == RBTREE_RED){
//         w->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         rotate_right(t, x->parent);
//         w = x->parent->left;
//       }
//       // Case 2
//       if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
//         w->color = RBTREE_RED;
//         x = x->parent;
//       }
//       // Case 3
//       else{ 
//       if (w->left->color == RBTREE_BLACK) {
//         w->right->color = RBTREE_BLACK;
//         w->color = RBTREE_RED;
//         rotate_left(t, w);
//         w = x->parent->left;
//       }
//       // Case 4
//       w->color = x->parent->color;
//       x->parent->color = RBTREE_BLACK;
//       w->left->color = RBTREE_BLACK;
//       rotate_right(t, x->parent);
//       x = t->root;
//     }
//   }
//   }
//   x->color = RBTREE_BLACK;
// }


// int rbtree_erase(rbtree *t, node_t *p) {
//   // TODO: implement erase
//   node_t *x;
//   node_t *y = p;
//   color_t original_color = y->color;
//   if (p->left == t->nil){
//     x = p->right;
//     rb_transplant(t, p, p->right);
//   }
//   else if (p->right == t->nil){
//     x = p->left;
//     rb_transplant(t, p, p->left);
//   }
//   else{
//     y = p->right;
//     node_t *current = p->right;
//     while (current->left != t->nil){
//       y = current;
//       current = current->left;
//     }
//     original_color = y->color;
//     x = y->right;
//     if (y->parent == p){
//       x->parent = y;
//     }
//     else{
//       rb_transplant(t, y, y->right);
//       y->right = p->right;
//       y->right->parent = y;
//     }
//     rb_transplant(t, p, y);
//     y->left = p->left;
//     y->left->parent = y;
//     y->color = p->color;
//   }

//   if (original_color == RBTREE_BLACK){
//     delete_fixup(t, x);
//   }
//   return 0;
// }


void rbtree_erase_fixup(rbtree *t, node_t *x){
  while (x != t->root && x->color==RBTREE_BLACK)   
  {
    if(x == x->parent->left){                       // 왼쪽에 붙어 있을때 
      node_t *w = x->parent->right;                 // 임시 노드에 형제 노드 할당
      if(w->color == RBTREE_RED){                   // 형제가 red일때
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rotate_left(t, x->parent);
        w = x->parent->right;
      }                                             // 형제 왼쪽 자식이 블랙이면서 오른쪽 자식도 블랙일때
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }else{                                        // 형제 자식 중 하나라도 레드면
        if (w->right->color == RBTREE_BLACK){
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rotate_right(t, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        rotate_left(t, x->parent);
        x = t->root;
      }
    }else{                                          // 오른쪽에 붙어 있을때 
      node_t *w = x->parent->left;
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        rotate_right(t, x->parent);
        w = x->parent->left;
      }
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      }else{ 
        if (w->left->color == RBTREE_BLACK){
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          rotate_left(t, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        rotate_right(t, x->parent);
        x = t->root;
      }      
    }
  }
  x->color = RBTREE_BLACK;
}

void rbtree_transplant(rbtree *t, node_t *u, node_t *v){

  if (u->parent == t->nil){
    t->root = v;
  }else if (u == u->parent->left){
    u->parent->left = v;
  }else{
    u->parent->right = v;
  }
  v->parent = u->parent;
}

int rbtree_erase(rbtree *t, node_t *d_node) {     // 삭제할 노드 받음
  // TODO: implement erase
  node_t *cur = d_node;                           // 삭제할 노드 임시 노드로 할당
  color_t cur_color = cur->color;                 // 제거할 노드의 색 저장 변수
  node_t *x;                                      // 임시 노드

  if (d_node->left == t->nil)                     // 삭제할 노드의 왼쪽이 nil일떄
  {                                               // 삭제할 놈과 그 오른쪽 자식의 부모들을 바꿈
    x = d_node->right;                            
    rbtree_transplant(t, d_node, d_node->right);
  }else if (d_node->right == t->nil){             // 오른쪽 놈이 nil이면
    x = d_node->left;                             // 외쪽 자식의 부모와 삭제할 부모 바꿔
    rbtree_transplant(t, d_node, d_node->left);
  }else{                                          // 만약 두자식 다 있으면
    cur = erase_min(d_node->right, t->nil);       // 오른쪽의 최소값 찾아(이분탐색 삭제와 동일)
    cur_color = cur->color;                       // 오른쪽 최소값의 색을 저장(이분탐색 삭제와 다른점)
    x = cur->right;                               
    if (cur->parent == d_node){                   // 최솟값의 부모가 삭제할 놈이면 cur를 cur의 오른쪽 부모로
      x->parent = cur;                            
    }else {                                       // 삭제할 놈이 아니면 최솟값 노드와 그 오른쪽 자식의 부모를 서로 바꾸고
      rbtree_transplant(t, cur, cur->right);
      cur->right = d_node->right;                 // 최솟값 자식을 삭제할 놈의 자식으로 붙힘
      cur->right->parent = cur;                   
    }
    rbtree_transplant(t, d_node, cur);            // 두 조건이 모두 아니면 최솟값을 삭제할 놈으로 대치하고 색은 삭제할 노드 색으로 
    cur->left = d_node->left;
    cur->left->parent = cur;
    cur->color = d_node->color;
  }
  free(d_node);                                   // 노드 삭제
  d_node = NULL;

  if(cur_color == RBTREE_BLACK){
    rbtree_erase_fixup(t, x);                     // 아래에서 삭제했던 놈이 블랙이면 rbtree 규칙에 위반 되므로 fixup과정 진행!
  }                                               
  t->nil->parent = NULL;
  t->nil->right = NULL;
  t->nil->left = NULL;
  t->nil->color = RBTREE_BLACK;
  
  return 0;
}

void inorder_traversal(rbtree *t, node_t *node, key_t *arr, key_t n){
  if (inorder_count >= n){
    return;
  }
  if (node->left){
    inorder_traversal(t, node->left, arr, n);
  }
  if (node != t->nil){
    arr[inorder_count] = node->key;
    inorder_count++;
    }
  if (node->right){
    inorder_traversal(t, node->right, arr, n);
  }
} 

key_t rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  inorder_count = 0;
  inorder_traversal(t, t->root, arr, n);
  return 0;
}