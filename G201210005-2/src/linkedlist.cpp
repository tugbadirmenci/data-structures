/**
 * odevv
 * txt dosyası içerisindeki sayıları gruplandırdıktan sonra kullanıcıdan indeks alıp yerlerini değiştiriyor ve  ortalama toplamı alıyor ust ve alt şeklinde ekranda yazdırıyor
 * 2.ogretim A grubu 
 * odev 1 
 * 27.07.2023
 * Tugba Dirmenci / tugba.dirmenci@ogr.sakarya.edu.tr
 */


#include <iostream>
#include <iomanip>
#include "linkedlist.hpp"

using namespace std;

void printDownwardLinkedList(Node* head) { //aşağı yönlü bağıl liste yazdır
    if (head == nullptr) {
        return; //liste sonunda fonksiyondan çık 
    }
    printDownwardLinkedList(head->next); // liste sonuna kadar özyineleme yap
    cout << head->data << " "; // listenin elemanlarını yazdır 
}

void printUpwardLinkedList(Node* head) { // yukarı yönlü b.listeleri yazdır
    if (head == nullptr) {
        return;
    }
    printUpwardLinkedList(head->next);
    cout << head->data << " ";
}

void printAllDownwardLists(Node** konumB, int satir_sayisi) { // tüm aşağı yönlü b.listeleri yazdır 
    cout << "Aşağı Yönlü Bağıl Listeler:" << endl;
    for (int i = 0; i < satir_sayisi; i++) {
        printDownwardLinkedList(konumB[i]);
        cout << endl;
    }
}

void printAllUpwardLists(Node** konumA, int satir_sayisi) { //tüm yukarı yönlü b.listeleri yazdır
    cout << "Yukarı Yönlü Bağıl Listeler:" << endl;
    for (int i = 0; i < satir_sayisi; i++) {
        printUpwardLinkedList(konumA[i]);
        cout << endl;
    }
}

void calculateAverage(Node** konumA, Node** konumB, int satir_sayisi) { //bağıl listelerin ortalma değerlerini hesapla ve ekrana yazdır
    double upTotal = 0.0; //tüm yukarı yönlü b.listelerin elemanları toplamı tutan değişken
    double downTotal = 0.0; //aşağı yönlü b.listelerin elemanları toplamını tutan değişken

    for (int i = 0; i < satir_sayisi; i++) {
        int upCount = 0; // yukarı yönlü b. listelerin eleman sayısı 
        int downCount = 0; // aşağı yönlü b. listelerin eleman sayısı 

        double upAverage = 0.0; // yukarı yönlü b.listelerin ortalama değeri 
        double downAverage = 0.0; // aşağı yönlü b. listelerin ortalama değeri

        Node* upTemp = konumA[i]; // yukarı yönlü b. listeler için geçici düğüm işaretçisi 
        while (upTemp != nullptr) {
            upAverage += upTemp->data; // düğüm verisini toplam değere ekle 
            upCount++;// eleman sayısını bir artır
            upTemp = upTemp->next; // sonraki düğüme geç 
        }

        Node* downTemp = konumB[i]; // aşağı yönlü b listeler için geçici düğüm işaretçisi 
        while (downTemp != nullptr) {
            downAverage += downTemp->data; // düğüm verisini toplam değere ekle 
            downCount++; // eleman sayısını arttır 
            downTemp = downTemp->next; // sonraki düğüme geç 
        }

        upAverage /= upCount; // yukarı yönlü b. listelerin ortalama değeri hesapla
        downAverage /= downCount; // aşağı yönlü b.listelerin ortalama değeri hesapla 

        upTotal += upAverage; // yukarı yönlü b. listelerin ortalama toplamı 
        downTotal += downAverage; // aşağı yönlü b listelerin ortalama toplamı 
    }

    cout << "Ust: " << upTotal << endl; // yukarı yönlü b. listelerin ortalama toplam değerini ekrana yazdır
    cout << "Alt: " << downTotal << endl; // aşağı yönlü b. listelerin ortalama toplam değerini ekrana yazdır
}