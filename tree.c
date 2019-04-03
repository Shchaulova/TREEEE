//
// Created by Светлана on 22.03.2019.
//

#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct TreeElement *TreeElement_CreateNode(TreeValueType new_value, struct TreeElement *head) {
    struct TreeElement *new_node = (struct TreeElement *)calloc(1, sizeof(struct TreeElement));
    new_node->value = new_value;
    new_node->depth = 1;
    new_node->head = head;
    return new_node;
}

void TreeElement_FreeNode(struct TreeElement *head) {
    free(head);
}

struct TreeElement *TreeElement_Clear(struct TreeElement *root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left) {
        TreeElement_Clear(root->left);
    }
    if (root->right) {
        TreeElement_Clear(root->right);
    }
    TreeElement_FreeNode(root);
    return NULL;
}

void TreeElement_CalcDepth(struct TreeElement *head) {
    int ldepth = head->left != NULL ? head->left->depth : 0;
    int rdepth = head->right != NULL ? head->right->depth : 0;
    head->depth = (ldepth > rdepth ? ldepth : rdepth) + 1;
}

struct TreeElement *TreeElement_LittleLeftRotate(struct TreeElement *head) {
    struct TreeElement *right = head->right;
    head->right = right->left;
    right->left = head;
    right->head = head->head;
    head->head = right;
    TreeElement_CalcDepth(head);
    TreeElement_CalcDepth(right);
    return right;
}

struct TreeElement *TreeElement_LittleRightRotate(struct TreeElement *head) {
    struct TreeElement *left = head->left;
    head->left = left->right;
    left->right = head;
    left->head = head->head;
    head->head = left;
    TreeElement_CalcDepth(head);
    TreeElement_CalcDepth(left);
    return left;
}

struct TreeElement *TreeElement_BigLeftRotate(struct TreeElement *head) {
    head->right = TreeElement_LittleRightRotate(head->right);
    return TreeElement_LittleLeftRotate(head);
}

struct TreeElement *TreeElement_BigRightRotate(struct TreeElement *head) {
    head->left = TreeElement_LittleLeftRotate(head->left);
    return TreeElement_LittleRightRotate(head);
}

struct TreeElement *TreeElement_Balancing(struct TreeElement *head) {
    int left_depth = head->left != NULL ? head->left->depth : 0;
    int right_depth = head->right != NULL ? head->right->depth : 0;

    int balance = right_depth - left_depth;

    if (balance == -2) {
        int ll_depth = head->left->left ? head->left->left->depth : 0;
        int lr_depth = head->left->right ? head->left->right->depth : 0;
        if (lr_depth - ll_depth > 0) {
            head = TreeElement_BigRightRotate(head);
        } else {
            head = TreeElement_LittleRightRotate(head);
        }
    } else if (balance == 2) {
        int rl_depth = head->right->left ? head->right->left->depth : 0;
        int rr_depth = head->right->right ? head->right->right->depth : 0;
        if (rr_depth - rl_depth < 0) {
            head = TreeElement_BigLeftRotate(head);
        } else {
            head = TreeElement_LittleLeftRotate(head);
        }
    } else {
        TreeElement_CalcDepth(head);
    }
    return head;
}

struct TreeElement *TreeElement_Insert(struct TreeElement *head, TreeValueType new_value) {
    if (head == NULL) {
        return TreeElement_CreateNode(new_value, NULL);
    }
    if (new_value == head->value) {
        return head;
    } else if (new_value > head->value) {
        if (head->right == NULL) {
            head->right = TreeElement_CreateNode(new_value, head);
        } else {
            head->right = TreeElement_Insert(head->right, new_value);
        };
    } else {
        if (head->left == NULL) {
            head->left = TreeElement_CreateNode(new_value, head);
        } else {
            head->left = TreeElement_Insert(head->left, new_value);
        }
    }

    return TreeElement_Balancing(head);
}


void TreeElement_Print(const struct TreeElement *head) {
    printf("(");
    if(head->left != NULL) {
        TreeElement_Print(head->left);
    }
    printf("%lf", head->value);
    if(head->right != NULL) {
        TreeElement_Print(head->right);
    }
    printf(")");
}

const struct TreeElement *TreeElement_Find(const struct TreeElement *head, TreeValueType value_to_find) {
    if (head == NULL) {
        return NULL;
    }
    if (head->value == value_to_find) {
        return head;
    }
    if (value_to_find < head->value) {
        if (head->left == NULL) {
            return NULL;
        }
        return TreeElement_Find(head->left, value_to_find);
    }
    if (head->right == NULL) {
        return NULL;
    }
    return TreeElement_Find(head->right, value_to_find);
}

struct TreeElement *TreeElement_Remove(struct TreeElement *head, TreeValueType value_to_remove) {
    if (head == NULL) {
        return NULL;
    }
    if (head->value != value_to_remove) {
        if (value_to_remove > head->value) {
            head->right = TreeElement_Remove(head->right, value_to_remove);
        } else {
            head->left = TreeElement_Remove(head->left, value_to_remove);
        }
    } else {
        if (head->left == NULL && head->right == NULL) {
            TreeElement_FreeNode(head);
            return NULL;
        }

        struct TreeElement *element_to_swap = head;
        int left_depth = element_to_swap->left != NULL ? element_to_swap->left->depth : 0;
        int right_depth = element_to_swap->right != NULL ? element_to_swap->right->depth : 0;

        if (left_depth > right_depth) {
            for (element_to_swap = head->left;
                 element_to_swap->right != NULL; element_to_swap = element_to_swap->right);
        } else {
            for (element_to_swap = head->right;
                 element_to_swap->left != NULL; element_to_swap = element_to_swap->left);
        }
        TreeValueType c = element_to_swap->value;
        element_to_swap->value = head->value;
        head->value = c;

        if (left_depth > right_depth) {
            head->left =  TreeElement_Remove(head->left, value_to_remove);
        } else {
            head->right =  TreeElement_Remove(head->right, value_to_remove);
        }
    }
    return TreeElement_Balancing(head);
}
