#ifndef BSTLINKEDLIST_HPP
#define BSTLINKEDLIST_HPP

#include "BST.hpp"

struct BSTNode2 {
    BST data;
    BSTNode2* next;
};

class BSTLinkedList {
public:
    BSTNode2* head;
    BSTNode2* tail;

    BSTLinkedList();
    void insert(BST data);
};

#endif // BSTLINKEDLIST_HPP
