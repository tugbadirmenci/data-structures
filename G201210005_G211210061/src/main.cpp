/**
 * @G201210005_G211210061
 * Seçilen maksimum yüksekliğe sahip ikili arama ağacı postorder okunup sayısal değerlerin ASCII karakter karşılıkları ekrana yazar.
 * odev2
 * 1.öğretim 2 A 
 * 30/07/2023
 * Tuğba Dirmenci Aslı Döngez
 * tugba.dirmenci@ogr.sakarya.edu.tr
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.hpp"
#include "BST.hpp"
#include "StackLinkedList.hpp"
#include "BSTLinkedList.hpp"

using namespace std;

int main() {
    ifstream file("Sayilar.txt"); // Dosyayı okumak için aç
    if (file.is_open()) { // Eğer dosya açıldıysa
        string line; // Her satır için bir string tanımla
        while (getline(file, line)) { // Dosyadan satır satır oku
            // Satırı boşluklara göre böl ve sayıları bir bağlı listeye kaydet
            LinkedList numbers;
            int number;
            istringstream iss(line);
            while (iss >> number) {
                numbers.insert(number);
            }

            // Sayıları yığıtlara bölme işlemi için bir yığıt bağlı listesi oluştur
            StackLinkedList stacks;

            // Bağlı listedeki her sayı için
            Node* current = numbers.head;
            while (current != NULL) {
                // Eğer yığıt bağlı listesi boşsa, yeni bir yığıt oluştur ve sayıyı ekle
                if (stacks.isEmpty()) {
                    stack<int> s;
                    s.push(current->data);
                    stacks.insert(s);
                }
                else {
                    // Eğer sayı çift ve o an işlem yapılan yığıttan çıkmak üzere olan sayıdan büyükse, yeni bir yığıta ekle
                    if (current->data % 2 == 0 && current->data > stacks.tail->data.top()) {
                        stack<int> s;
                        s.push(current->data);
                        stacks.insert(s);
                    }
                    else {
                        // Değilse, mevcut yığıta ekle
                        stacks.tail->data.push(current->data);
                    }
                }
                current = current->next;
            }

            // Yığıtları ikili arama ağaçlarına dönüştürme işlemi için bir BST bağlı listesi oluştur
            BSTLinkedList trees;

            // Yığıt bağlı listesindeki her yığıt için
            StackNode* currentStack = stacks.head;
            while (currentStack != NULL) {
                // Yeni bir BST oluştur
                BST tree;

                // Yığıttaki her sayıyı BST'ye ekle (aynı değerleri engelle)
               while (!currentStack->data.empty())  {
                    tree.insert(currentStack->data.top());
                    currentStack->data.pop();
                }

                // BST'yi BST bağlı listesine ekle
                trees.insert(tree);

                currentStack = currentStack->next;
            }

            // Her satır için, oluşan ağaçlardan en büyük yüksekliğe sahip ağacı seçmek için bir pointer tanımla
            BSTNode2* maxTree = NULL;

            // BST bağlı listesindeki her ağaç için
            BSTNode2* currentTree = trees.head;
            while (currentTree != NULL) {
                if (maxTree == NULL) { // Eğer maksimum ağaç pointer'ı NULL ise, ilk ağacı ata
                    maxTree = currentTree;
                }
                else { // Değilse, yükseklikleri karşılaştır
                    int currentHeight = currentTree->data.height();
                    int maxHeight = maxTree->data.height();
                    if (currentHeight > maxHeight) { // Eğer şimdiki ağacın yüksekliği daha büyükse, maksimum ağaç pointer'ını güncelle
                        maxTree = currentTree;
                    }
                    else if (currentHeight == maxHeight) { // Eğer yükseklikler eşitse, düğüm değerleri toplamlarını karşılaştır
                        int currentSum = currentTree->data.sum();
                        int maxSum = maxTree->data.sum();
                        if (currentSum > maxSum) { // Eğer şimdiki ağacın toplamı daha büyükse, maksimum ağaç pointer'ını güncelle
                            maxTree = currentTree;
                        }
                        // Toplamlar da eşitse, önce oluşturulan ağacı seçmek için bir şey yapmaya gerek yok
                    }
                }
                currentTree = currentTree->next;
            }

            // Seçilen maksimum yüksekliğe sahip ağacı postorder olarak yazdır
            maxTree->data.postorder();

            // Ekranda 10 milisaniye sleep fonksiyonu kullanarak bekle
            //Sleep(10);
        }
        file.close(); // Dosyayı kapat
    }
    else { // Eğer dosya açılamadıysa, hata mesajı yazdır
        cout << "Dosya okunamadi!" << endl;
    }
    return 0;
}

