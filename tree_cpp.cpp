//
// Created by Светлана on 22.03.2019.
//

#include "tree_cpp.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class Container

{

public:

    // Виртуальные методы, будут реализованы далее

    virtual void insert(int value) = 0;

    virtual bool exists(int value) = 0;

    virtual void remove(int value) = 0;

    // Это потом заменим на перегруженный оператор <<

    virtual void print() = 0;

protected:

    // Виртуальный деструктор

    virtual ~Container();

};



Container::~Container() { }



// Реализация интерфейса



// TODO



int main()

{

    Container* c = new SimpleTree();



    for(int i = 1; i < 10; i++)

        c->insert(i*i);



    printf("List after creation:\n");

    c->print();



    if(c->exists(25))

        cout << "Search for value 25: found" << endl;



    if(!c->exists(111))

        cout << "Search for value 111: not found" << endl;



    c->remove(25);

    cout << "List after deletion of the element:" << endl;

    c->print();



    delete c;

    return 0;

}
void Tree::Element::CalcDepth() {
    int ldepth = left != NULL ? left->depth : 0;
    int rdepth = right != NULL ? right->depth : 0;
    depth = (ldepth > rdepth ? ldepth : rdepth) + 1;
}

Tree::Element *Tree::Element::LittleLeftRotate() {
    Element *right = this->right;
    this->right = right->left;
    right->left = this;
    right->head = this->head;
    this->head = right;
    CalcDepth();
    right->CalcDepth();
    return right;
}

Tree::Element *Tree::Element::LittleRightRotate() {
    Element *left = this->left;
    this->left = left->right;
    left->right = this;
    left->head = this->head;
    this->head = left;
    CalcDepth();
    left->CalcDepth();
    return left;
}

Tree::Element *Tree::Element::BigLeftRotate() {
    right = right->LittleRightRotate();
    return LittleLeftRotate();
}

Tree::Element *Tree::Element::BigRightRotate() {
    left = left->LittleLeftRotate();
    return LittleRightRotate();
}

Tree::Element *Tree::Element::Insert(Tree::TreeValueType new_value) {
    if (new_value == this->value) {
        return this;
    } else if (new_value > this->value) {
        if (right == nullptr) {
            right = new Element{new_value, this};
        } else {
            right = right->Insert(new_value);
        };
    } else {
        if (left == nullptr) {
            left = new Element{new_value, this};
        } else {
            left = left->Insert(new_value);
        }
    }

    return Balancing(this);
}

Tree::Element *Tree::Element::Balancing(Element *head) {
    int left_depth = head->left != nullptr ? head->left->depth : 0;
    int right_depth = head->right != nullptr ? head->right->depth : 0;

    int balance = right_depth - left_depth;

    if (balance == -2) {
        int ll_depth = head->left->left ? head->left->left->depth : 0;
        int lr_depth = head->left->right ? head->left->right->depth : 0;
        if (lr_depth - ll_depth > 0) {
            head = head->BigRightRotate();
        } else {
            head = head->LittleRightRotate();
        }
    } else if (balance == 2) {
        int rl_depth = head->right->left ? head->right->left->depth : 0;
        int rr_depth = head->right->right ? head->right->right->depth : 0;
        if (rr_depth - rl_depth < 0) {
            head = head->BigLeftRotate();
        } else {
            head = head->LittleLeftRotate();
        }
    } else {
        head->CalcDepth();
    }
    return head;
}

std::ostream &operator<<(std::ostream &os, const Tree::Element &element) {
    os << "(";
    if (element.left) {
        os << *element.left;
    }
    os << element.value;
    if (element.right) {
        os << *element.right;
    }
    return os << ")";
}

const bool Tree::Element::exists(const Tree::TreeValueType &value_to_find) const {
    if (value == value_to_find) {
        return true;
    }
    if (value_to_find < value) {
        if (left == nullptr) {
            return false;
        }
          return true;
//        return left->Find(value_to_find);
    }
    if (head->right == nullptr) {
        return false;
    }
    return right->Find(value_to_find);
}

Tree::Element *Tree::Element::Remove(Element *head, Tree::TreeValueType value_to_remove) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->value != value_to_remove) {
        if (value_to_remove > head->value) {
            head->right = Remove(head->right, value_to_remove);
        } else {
            head->left = Remove(head->left, value_to_remove);
        }
    } else {
        if (head->left == nullptr && head->right == nullptr) {
            delete head;
            return nullptr;
        }

        Element *element_to_swap = head;
        int left_depth = element_to_swap->left != nullptr ? element_to_swap->left->depth : 0;
        int right_depth = element_to_swap->right != nullptr ? element_to_swap->right->depth : 0;

        if (left_depth > right_depth) {
            for (element_to_swap = head->left;
                 element_to_swap->right != nullptr; element_to_swap = element_to_swap->right);
        } else {
            for (element_to_swap = head->right;
                 element_to_swap->left != nullptr; element_to_swap = element_to_swap->left);
        }
        TreeValueType c = element_to_swap->value;
        element_to_swap->value = head->value;
        head->value = c;

        if (left_depth > right_depth) {
            head->left =  Remove(head->left, value_to_remove);
        } else {
            head->right =  Remove(head->right, value_to_remove);
        }
    }
    return Balancing(head);
}

void Tree::Element::Clear(Tree::Element *root) {
    if (root == nullptr) {
        return;
    }
    if (root->left) {
        Clear(root->left);
    }
    if (root->right) {
        Clear(root->right);
    }
    delete root;
}

void Tree::Insert(Tree::TreeValueType value) {
    if (root != nullptr) {
        root = root->Insert(value);
    } else {
        root = new Element{value, nullptr};
    }
}

std::ostream &operator<<(std::ostream &os, const Tree &tree) {
    return os << *tree.root;
}

const Tree::Element *Tree::Find(const Tree::TreeValueType &value_to_find) const {
    if (root != nullptr) {
        return root->Find(value_to_find);
    }
    return nullptr;
}

void Tree::Remove(const Tree::TreeValueType &value_to_remove) {
    root = Element::Remove(root, value_to_remove);
}

Tree::~Tree() {
    Element::Clear(root);
    root = nullptr;
}
