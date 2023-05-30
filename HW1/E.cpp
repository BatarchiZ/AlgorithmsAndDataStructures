//
// Created by Iskander Sergazin on 26/10/2022.
// Read Implementation in from link you've sent -> great implementation btw

#ifndef HW2_RBTREE_H
#define HW2_RBTREE_H

#include <string>

struct Node {
    Node();

    Node(std::string str, std::string val)
            : key(str), _value(val) {
    };
    std::string _value;
    std::string key;
    bool colour = false;

    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
    Node *parent = nullptr;
};

class RBTree {

    void _leftRotate(Node *pivot);

    void _rightRotate(Node *pivot);

    void _insertFix(Node *pivot);

    void _transplant(Node *pivot1, Node *pivot2);

    Node *treeMin(Node *cur);

    void _deleteFixup(Node *cur);

public:
    void insertF(Node *pivot);

    void rbDelete(Node *pivot);

    Node *root = nullptr;
};


void RBTree::_deleteFixup(Node *p) {
    while (p->colour == 0 && p != root) {
        if (p == p->parent->leftChild) {
            Node *brother = p->parent->rightChild;
            if (p->parent->rightChild && p->parent->rightChild->colour == 1) {
                brother->colour = 0;
                brother->parent->colour = 1;
                _leftRotate(brother->parent);
            }
            if ((brother && brother->leftChild && brother->rightChild && brother->leftChild->colour == 0 &&
                 brother->rightChild->colour == 0) || (!brother->leftChild && !brother->rightChild)) {
                brother->colour = 1;
            }
            else {
                if (!brother->rightChild || (brother->rightChild && brother->rightChild->colour == 0)) {
                    if (brother->leftChild) {
                        brother->leftChild = 0;
                    }
                    brother->colour = 1;
                    _rightRotate(brother);
                }
                brother->colour = p->parent->colour;
                p->parent->colour = 0;
                brother->rightChild->colour = 0;
                _leftRotate(p->parent);
                p = root;
            }
        }
        else {
            Node *brother = p->parent->leftChild;
            if (brother && brother->colour == 1) {
                brother->colour = 0;
                brother->parent->colour = 1;
                _rightRotate(brother->parent);
            }
            if ((brother && brother->leftChild && brother->rightChild && brother->leftChild->colour == 0 &&
                 brother->rightChild->colour == 0) || (!brother->leftChild && !brother->rightChild)) {
                brother->colour = 1;
            }
            else {
                if (!brother->leftChild || (brother->leftChild && brother->leftChild->colour == 0)) {
                    if (brother->rightChild) {
                        brother->rightChild = 0;
                    }
                    brother->colour = 1;
                    _leftRotate(brother);
                }
                brother->colour = p->parent->colour;
                p->parent->colour = 0;
                brother->leftChild->colour = 0;
                _rightRotate(p->parent);
                p = root;
            }
        }

    }
    p->colour = 0;
    root->colour = 0;
}

Node *RBTree::treeMin(Node *cur) {
    Node *prev = nullptr;
    while (cur) {
        prev = cur;
        cur = cur->leftChild;
    }
    return prev;
}

void RBTree::rbDelete(Node *pivot) {
    Node *p = root;
    while (p->key != pivot->key) {
        if (p->key < pivot->key) {
            p = p->rightChild;
        }
        else {
            p = p->leftChild;
        }
    }
    if (!p->leftChild && !p->rightChild) {
        if (p == root) {
            root = nullptr;
        }
        else {
            if (p == p->parent->leftChild) {
                p->parent->leftChild = nullptr;
            }
            else {
                p->parent->rightChild = nullptr;
            }
            return;
        }
    }
    Node *y = nullptr;
    Node *q = nullptr;
    if ((p->leftChild && !p->rightChild) || (p->rightChild && !p->leftChild)) {
        if (p->leftChild && !p->rightChild) {
            p->leftChild->parent = p->parent;
        }
        else {
            p->rightChild->parent = p->parent;
            if (p->rightChild->parent == nullptr) {
                root = p->rightChild;
            }
        }
    }
    else {
        y = treeMin(pivot->rightChild);
        if (!y) {
            return;
        }
        if (y->rightChild) {
            y->rightChild->parent = y->parent;
        }
        if (y == root) {
            root = y->rightChild;
        }
        else {
            if (y == y->parent->rightChild) {
                y->parent->rightChild = y->rightChild;
            }
            else {
                y->parent->leftChild = y->rightChild;
            }
        }
    }
    if (y && p && y != p) {
        p->colour = y->colour;
        p->key = y->key;
    }
    if (y && y->colour == 0) {
        _deleteFixup(q);
    }
    delete pivot;
}


void RBTree::_insertFix(Node *pivot) {
    if (pivot == root) {
        pivot->colour = 0;
        return;
    }
    while (pivot->parent->colour == 1) {
        if (pivot->parent == pivot->parent->leftChild) {
            if (pivot->parent->rightChild && pivot->parent->rightChild->colour == 1) {
                pivot->parent->colour = 0;
                pivot->parent->rightChild = 0;
                pivot->parent->parent->colour = 1;
                pivot = pivot->parent->parent;
            }
            else {
                if (pivot == pivot->parent->rightChild) {
                    pivot = pivot->parent;
                    _leftRotate(pivot);
                }
                pivot->parent->colour = 0;
                pivot->parent->parent->colour = 1;
                _rightRotate(pivot->parent->parent);
            }
        }
        else {
            if (pivot->parent->leftChild && pivot->parent->leftChild->colour == 1) {
                pivot->parent->colour = 0;
                pivot->parent->leftChild->colour = 0;
                pivot->parent->parent->colour = 1;
                pivot = pivot->parent->parent;
            }
            else {
                if (pivot == pivot->parent->leftChild) {
                    pivot = pivot->parent;
                    _rightRotate(pivot);
                }
                pivot->parent->colour = 0;
                pivot->parent->parent->colour = 1;
                _leftRotate(pivot->parent->parent);
            }
        }
    }

}

void RBTree::insertF(Node *pivot) {
    if (!root) {
        root = pivot;
        pivot->parent = nullptr;
    }
    else {
        Node *p = root;
        Node *q = nullptr;
        while (p != nullptr) {
            q = p;
            if (p->key < pivot->key) {
                p = p->rightChild;
            }
            else {
                p = p->leftChild;
            }
            pivot->parent = q;
        }
        if (q->key < pivot->key) {
            q->rightChild = pivot;
        }
        else {
            q->leftChild = pivot;
        }
    }
    _insertFix(pivot);
}

void RBTree::_leftRotate(Node *pivot) {
    Node *left = pivot->rightChild;
    pivot->rightChild = left->leftChild;
    if (left->leftChild != nullptr) {
        left->leftChild->parent = pivot;
    }
    if (pivot->parent) {
        this->root = left;
    }
    else if (pivot == pivot->parent->leftChild) {
        pivot->parent->leftChild = left;
    }
    else {
        pivot->parent->rightChild = left;
    }
    left->leftChild = pivot;
    pivot->parent = left;
}

void RBTree::_rightRotate(Node *pivot) {
    Node *right = pivot->rightChild;
    pivot->leftChild = right->rightChild;
    if (right->rightChild) {
        right->rightChild->parent = pivot;
    }
    if (pivot->parent) {
        this->root = right;
    }
    else if (pivot == pivot->parent->leftChild) {
        pivot->parent->leftChild = right;
    }
    else {
        pivot->parent->rightChild = right;
    }
    right->rightChild = pivot;
    pivot->parent = right;
}


#endif //HW2_RBTREE_H

#include <fstream>
#include <sstream>
#include <iostream>

Node *find(Node *root, std::string query) {
    Node *cur = root;
    while (cur) {
        if (query == cur->key) {
            return cur;
        }
        else if (query < cur->key) {
            cur = cur->leftChild;
        }
        else {
            cur = cur->rightChild;
        }
    }
    return cur;
}

void RBInsert(RBTree &rbt, std::string str, std::string val) {
    Node *temp = find(rbt.root, str);
    if (temp) {
        std::cout << "Exist" << std::endl;
        return;
    }
    else {
        Node *cur = new Node(str, val);
        rbt.insertF(cur);
        std::cout << "OK" << std::endl;
    }
}

void RBDelete(RBTree &rbt, std::string str) {
    Node *temp = find(rbt.root, str);
    if (!temp) {
        std::cout << "NoSuchWord" << std::endl;
        return;
    }
    else {
        rbt.rbDelete(temp);
        std::cout << "OK" << std::endl;
    }
}

void RBSearch(RBTree &rbt, std::string str) {
    Node *temp = find(rbt.root, str);
    if (temp) {
        std::cout << "OK: " << temp->_value << std::endl;
    }
    else {
        std::cout << "NoSuchWord" << std::endl;
    }
}

#include <algorithm>
#include <cctype>

std::string convtoLower(std::string &data) {
    std::string lowered;
    for (char &c: data) {
        lowered += tolower(c);
    }
    return lowered;
}


int main() {
//    const std::string INP_FILE_NAME = "/Users/iskandersergazin/Clion/HW2/input2.txt";
    const std::string INP_FILE_NAME = "input.txt";
    std::ifstream input_file;
    input_file.open(INP_FILE_NAME);
    if (!input_file) {
        return 1;
    }
    std::string dummmy;

    RBTree rbt;
    while (getline(input_file, dummmy)) {
        if (dummmy[0] == '+') {
            std::stringstream ss;
            ss << dummmy;
            getline(ss, dummmy, ' ');
            std::string key;
            getline(ss, key, ' ');
            key = convtoLower(key);
            std::string value;
            getline(ss, value);
            RBInsert(rbt, key, value);
        }
        else if (dummmy[0] == '-') {
            std::stringstream ss;
            ss << dummmy;
            getline(ss, dummmy, ' ');
            std::string key;
            getline(ss, key);
            key = convtoLower(key);
            RBDelete(rbt, key);
        }
        else {
            std::stringstream ss;
            ss << dummmy;
            getline(ss, dummmy);
            dummmy = convtoLower(dummmy);
            RBSearch(rbt, dummmy);
        }
    }
    return 0;
}
