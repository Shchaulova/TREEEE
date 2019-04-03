//
// Created by Светлана on 22.03.2019.
//

#ifndef TREE_C_TREE_CPP_H
#define TREE_C_TREE_CPP_H

#include <ostream>

struct Tree {
public:
    using TreeValueType = double;

    struct Element {
    public:
        TreeValueType value;

    private:
        Element(TreeValueType value, Element *head)
                : value(value), head(head), depth(0), left(nullptr), right(nullptr) {}

        static void Clear(Element *head);

        void CalcDepth();

        Element *LittleLeftRotate();

        Element *LittleRightRotate();

        Element *BigLeftRotate();

        Element *BigRightRotate();

        Element *Insert(TreeValueType new_value);

        friend std::ostream &operator<<(std::ostream &os, const Element &element);

        static Element *Balancing(Element *head);

        const Element *Find(const TreeValueType &value) const;

        static Element *Remove(Element *head, TreeValueType value_to_remove);

        int depth;
        Element *head;
        Element *left;
        Element *right;

        friend Tree;
    };

    Tree() : root(nullptr) {}

    ~Tree();

    void Insert(TreeValueType value);

    const Element *Find(const TreeValueType &value_to_find) const;

    void Remove(const TreeValueType &value_to_remove);

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

private:

    Element *root;
};

#endif //TREE_C_TREE_CPP_H
