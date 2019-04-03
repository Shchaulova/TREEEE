#include <stdio.h>

#include "tree.h"

int main() {
    struct TreeElement *root = NULL;
//    for (int i = 0; i > -5; --i) {
//        root = TreeElement_Insert(root, i);
//        TreeElement_Print(root);
//        printf("\n");
//    }
//    int sign = 1;
//    for (int i = -10; i < 11; ++i, sign *= -1) {
//        root = TreeElement_Insert(root, sign * i);
//        TreeElement_Print(root);
//        printf("\n");
//    }
    for (int i = -5; i < 5; ++i) {
        root = TreeElement_Insert(root, i);
    }
    TreeElement_Print(root);
    printf("\n");
    root = TreeElement_Remove(root, 1);
    TreeElement_Print(root);
    printf("\n");
    TreeElement_Clear(root);
    return 0;
}