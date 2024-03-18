#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList();
    void insert(int data);
};

#endif // LINKEDLIST_HPP
