#include <iostream>

#include "tree_cpp.h"

int main() {
    Tree tree;
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
        tree.Insert(i);
    }
    std::cout << tree << std::endl;
    tree.Remove(1);
    std::cout << tree << std::endl;
    return 0;
}