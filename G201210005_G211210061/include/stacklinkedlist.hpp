#ifndef STACKLINKEDLIST_HPP
#define STACKLINKEDLIST_HPP

#include <stack>

struct StackNode {
    std::stack<int> data;
    StackNode* next;
};

class StackLinkedList {
public:
    StackNode* head;
    StackNode* tail;

    StackLinkedList();
    void insert(std::stack<int> data);
    bool isEmpty();
};

#endif // STACKLINKEDLIST_HPP
