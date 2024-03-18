/**
 * odevv
 * txt dosyası içerisindeki sayıları gruplandırdıktan sonra kullanıcıdan indeks alıp yerlerini değiştiriyor ve  ortalama toplamı alıyor ust ve alt şeklinde ekranda yazdırıyor
 * 2.ogretim A grubu 
 * odev 1 
 * 27.07.2023
 * Tugba Dirmenci / tugba.dirmenci@ogr.sakarya.edu.tr
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void printDownwardLinkedList(Node* head);//aşağı yönlü bağıl liste yazdıran fonksiyon

void printUpwardLinkedList(Node* head);//yukarı yönlü bağıl liste yazdıran fonksiyon

void printAllDownwardLists(Node** konumB, int satır_sayısı);

void printAllUpwardLists(Node** konumA, int satır_sayısı);

void calculateAverage(Node** konumA, Node** konumB, int satır_sayısı);//bağıl listelerin ortalamalarını hesaplayan fonksiyon

#endif // LINKEDLIST_HPP
