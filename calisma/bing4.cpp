#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
//#include <windows.h>

using namespace std;

// Bağlı liste düğümü tanımı
struct Node {
    int data;
    Node* next;
};

// Bağlı liste sınıfı tanımı
class LinkedList {
public:
    Node* head; // Bağlı listenin başını tutan pointer
    Node* tail; // Bağlı listenin sonunu tutan pointer

    // Boş bir bağlı liste oluşturan kurucu fonksiyon
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    // Bağlı listenin sonuna veri ekleyen fonksiyon
    void insert(int data) {
        Node* newNode = new Node; // Yeni bir düğüm oluştur
        newNode->data = data; // Düğümün verisini ata
        newNode->next = NULL; // Düğümün sonraki pointer'ını NULL yap

        if (head == NULL) { // Eğer bağlı liste boşsa, baş ve son pointer'ını yeni düğüme ata
            head = newNode;
            tail = newNode;
        }
        else { // Değilse, son düğümün sonraki pointer'ını yeni düğüme ata ve son pointer'ını güncelle
            tail->next = newNode;
            tail = newNode;
        }
    }
};

// İkili arama ağacı düğümü tanımı
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
};

// İkili arama ağacı sınıfı tanımı
class BST {
public:
    BSTNode* root; // Ağacın kökünü tutan pointer

    // Boş bir ağaç oluşturan kurucu fonksiyon
    BST() {
        root = NULL;
    }

    // Ağaca veri ekleyen fonksiyon (aynı değerleri engeller)
    void insert(int data) {
        root = insertHelper(root, data); // Yardımcı fonksiyonu çağırarak kök pointer'ını güncelle
    }

    // Ağacın yüksekliğini döndüren fonksiyon
    int height() {
        return heightHelper(root); // Yardımcı fonksiyonu çağırarak yüksekliği hesapla
    }

    // Ağacın düğüm değerlerinin toplamını döndüren fonksiyon
    int sum() {
        return sumHelper(root); // Yardımcı fonksiyonu çağırarak toplamı hesapla
    }

    // Ağacı postorder olarak yazdıran fonksiyon
    void postorder() {
        postorderHelper(root); // Yardımcı fonksiyonu çağırarak postorder yazdırma işlemini yap
        cout << endl; // Son olarak bir satır atla
    }

private:
    // Ağaca veri ekleyen yardımcı fonksiyon (aynı değerleri engeller)
    BSTNode* insertHelper(BSTNode* node, int data) {
        if (node == NULL) { // Eğer düğüm NULL ise, yeni bir düğüm oluştur ve verisini ata
            node = new BSTNode;
            node->data = data;
            node->left = NULL;
            node->right = NULL;
        }
        else if (data < node->data) { // Eğer veri düğümün verisinden küçükse, sol alt ağaca ekleme yap
            node->left = insertHelper(node->left, data);
        }
        else if (data > node->data) { // Eğer veri düğümün verisinden büyükse, sağ alt ağaca ekleme yap
            node->right = insertHelper(node->right, data);
        }
        return node; // Düğümü geri döndür
    }

    // Ağacın yüksekliğini döndüren yardımcı fonksiyon
    int heightHelper(BSTNode* node) {
        if (node == NULL) { // Eğer düğüm NULL ise, yükseklik 0
            return 0;
        }
        else { // Değilse, sol ve sağ alt ağaçların yüksekliklerini hesapla ve büyük olanı 1 arttırarak geri döndür
            int leftHeight = heightHelper(node->left);
            int rightHeight = heightHelper(node->right);
            return max(leftHeight, rightHeight) + 1;
        }
    }

    // Ağacın düğüm değerlerinin toplamını döndüren yardımcı fonksiyon
    int sumHelper(BSTNode* node) {
        if (node == NULL) { // Eğer düğüm NULL ise, toplam 0
            return 0;
        }
        else { // Değilse, düğümün verisi ile sol ve sağ alt ağaçların toplamlarının toplamını geri döndür
            int leftSum = sumHelper(node->left);
            int rightSum = sumHelper(node->right);
            return node->data + leftSum + rightSum;
        }
    }

    // Ağacı postorder olarak yazdıran yardımcı fonksiyon
    void postorderHelper(BSTNode* node) {
        if (node != NULL) { // Eğer düğüm NULL değilse, sol alt ağacı yazdır, sonra sağ alt ağacı yazdır, sonra düğümün verisinin ASCII karakter karşılığını yazdır
            postorderHelper(node->left);
            postorderHelper(node->right);
            cout << char(node->data) << " ";
        }
    }
};

// Yığıt bağlı listesi düğümü tanımı
struct StackNode {
    stack<int> data; // Yığıt verisi
    StackNode* next; // Sonraki pointer
};

// Yığıt bağlı listesi sınıfı tanımı
class StackLinkedList {
public:
    StackNode* head; // Bağlı listenin başını tutan pointer
    StackNode* tail; // Bağlı listenin sonunu tutan pointer

    // Boş bir yığıt bağlı listesi oluşturan kurucu fonksiyon
    StackLinkedList() {
        head = NULL;
        tail = NULL;
    }

    // Yığıt bağlı listenin sonuna yığıt ekleyen fonksiyon
    void insert(stack<int> data) {
        StackNode* newNode = new StackNode; // Yeni bir düğüm oluştur
        newNode->data = data; // Düğümün verisini ata
        newNode->next = NULL; // Düğümün sonraki pointer'ını NULL yap

        if (head == NULL) { // Eğer yığıt bağlı listesi boşsa, baş ve son pointer'ını yeni düğüme ata
            head = newNode;
            tail = newNode;
        }
        else { // Değilse, son düğümün sonraki pointer'ını yeni düğüme ata ve son pointer'ını güncelle
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Yığıt bağlı listenin boş olup olmadığını döndüren fonksiyon
    bool isEmpty() {
        return head == NULL; // Eğer baş pointer'ı NULL ise, yığıt bağlı listesi boş demektir
    }
};

// BST bağlı listesi düğümü tanımı
struct BSTNode2 {
    BST data; // BST verisi
    BSTNode2* next; // Sonraki pointer
};

// BST bağlı listesi sınıfı tanımı
class BSTLinkedList {
public:
    BSTNode2* head; // Bağlı listenin başını tutan pointer
    BSTNode2* tail; // Bağlı listenin sonunu tutan pointer

    // Boş bir BST bağlı listesi oluşturan kurucu fonksiyon
    BSTLinkedList() {
        head = NULL;
        tail = NULL;
    }

    // BST bağlı listenin sonuna BST ekleyen fonksiyon
    void insert(BST data) {
        BSTNode2* newNode = new BSTNode2; // Yeni bir düğüm oluştur
        newNode->data = data; // Düğümün verisini ata
        newNode->next = NULL; // Düğümün sonraki pointer'ını NULL yap

        if (head == NULL) { // Eğer BST bağlı listesi boşsa, baş ve son pointer'ını yeni düğüme ata
            head = newNode;
            tail = newNode;
        }
        else { // Değilse, son düğümün sonraki pointer'ını yeni düğüme ata ve son pointer'ını güncelle
            tail->next = newNode;
            tail = newNode;
        }
    }
};

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

