#include <assert.h>
#include "rbtree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    rbtree *testTree = new_rbtree();
    *rbtree_insert(testTree, 100);
    printf("%d\n", testTree->root->key);
    
    return 0;
}


