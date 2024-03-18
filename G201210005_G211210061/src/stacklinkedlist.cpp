/**
 * @G201210005_G211210061
 * Seçilen maksimum yüksekliğe sahip ikili arama ağacı postorder okunup sayısal değerlerin ASCII karakter karşılıkları ekrana yazar.
 * odev2
 * 1.öğretim 2 A 
 * 30/07/2023
 * Tuğba Dirmenci Aslı Döngez
 * tugba.dirmenci@ogr.sakarya.edu.tr
 */

#include "StacklinkedList.hpp"

StackLinkedList::StackLinkedList() {
    head = NULL;
    tail = NULL;
}

void StackLinkedList::insert(std::stack<int> data) {
    StackNode* newNode = new StackNode;
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

bool StackLinkedList::isEmpty() {
    return head == NULL;
}
