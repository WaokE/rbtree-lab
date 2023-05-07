#include <assert.h>
#include "rbtree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    rbtree *test_tree = new_rbtree();
    *rbtree_insert(test_tree, 100);
    printf("%d\n", test_tree->root->key);
    printf("%d\n", test_tree->root->color);

    return 0;
}


