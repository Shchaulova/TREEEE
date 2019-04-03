//
// Created by Светлана on 22.03.2019.
//

#ifndef TREE_C_TREE_H
#define TREE_C_TREE_H

typedef double TreeValueType;

struct TreeElement {
    TreeValueType value;
    int depth;

    struct TreeElement *head;
    struct TreeElement *left;
    struct TreeElement *right;
};

struct TreeElement *TreeElement_Insert(struct TreeElement *head, TreeValueType new_value);

struct TreeElement *TreeElement_Clear(struct TreeElement *root);

void TreeElement_Print(const struct TreeElement *head);

const struct TreeElement *TreeElement_Find(const struct TreeElement *head, TreeValueType value_to_find);

struct TreeElement *TreeElement_Remove(struct TreeElement *head, TreeValueType value_to_remove);


#endif //TREE_C_TREE_H
