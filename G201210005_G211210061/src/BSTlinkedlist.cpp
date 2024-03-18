/**
 * @G201210005_G211210061
 * Seçilen maksimum yüksekliğe sahip ikili arama ağacı postorder okunup sayısal değerlerin ASCII karakter karşılıkları ekrana yazar.
 * odev2
 * 1.öğretim 2 A 
 * 30/07/2023
 * Tuğba Dirmenci Aslı Döngez
 * tugba.dirmenci@ogr.sakarya.edu.tr
 */

#include "BSTLinkedList.hpp"

BSTLinkedList::BSTLinkedList() {
    head = 0;
    tail = 0;
}

void BSTLinkedList::insert(BST data) {
    BSTNode2* newNode = new BSTNode2;
    newNode->data = data;
    newNode->next = 0;

    if (head == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}
