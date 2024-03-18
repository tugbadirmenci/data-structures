#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std;

// Bir ikili arama ağacı düğümü tanımlayın
struct Node {
    int data; // Düğümün değeri
    Node* left; // Sol alt ağacın kökü
    Node* right; // Sağ alt ağacın kökü

    // Düğüm oluşturucu
    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

// Bir ikili arama ağacı sınıfı tanımlayın
class BST {
private:
    Node* root; // Ağacın kök düğümü

    // Ağaca bir düğüm ekleme yardımcı fonksiyonu
    void insertHelper(Node*& node, int data) {
        // Eğer ağaç boşsa, yeni düğümü kök yap
        if (node == NULL) {
            node = new Node(data);
        }
        // Eğer eklenecek değer düğümün değerinden küçükse, sol alt ağaca ekle
        else if (data < node->data) {
            insertHelper(node->left, data);
        }
        // Eğer eklenecek değer düğümün değerinden büyükse, sağ alt ağaca ekle
        else if (data > node->data) {
            insertHelper(node->right, data);
        }
        // Eğer eklenecek değer düğümün değerine eşitse, eklemeyi yapma (aynı değerleri engelle)
    }

    // Ağacın yüksekliğini hesaplama yardımcı fonksiyonu
    int heightHelper(Node* node) {
        // Eğer ağaç boşsa, yükseklik sıfır
        if (node == NULL) {
            return 0;
        }

        // Sol ve sağ alt ağaçların yüksekliklerini hesapla
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);

        // Yükseklik, alt ağaçların yüksekliklerinin en büyüğü artı bir
        return max(leftHeight, rightHeight) + 1;
    }

    // Ağacın düğüm değerlerinin toplamını hesaplama yardımcı fonksiyonu
    int sumHelper(Node* node) {
        // Eğer ağaç boşsa, toplam sıfır
        if (node == NULL) {
            return 0;
        }

        // Sol ve sağ alt ağaçların toplamlarını hesapla
        int leftSum = sumHelper(node->left);
        int rightSum = sumHelper(node->right);

        // Toplam, alt ağaçların toplamları artı düğümün değeri
        return leftSum + rightSum + node->data;
    }

    // Ağacı postorder sırada yazdırma yardımcı fonksiyonu
    void printPostorderHelper(Node* node) {
        // Eğer ağaç boşsa, hiçbir şey yazdırma
        if (node == NULL) {
            return;
        }

        // Sol alt ağacı yazdır
        printPostorderHelper(node->left);

        // Sağ alt ağacı yazdır
        printPostorderHelper(node->right);

        // Düğümün değerinin ASCII karakter karşılığını yazdır
        cout << char(node->data);
    }

public:
    // Ağaç oluşturucu
    BST() {
        this->root = NULL;
    }

    // Ağaca bir düğüm ekleme fonksiyonu
    void insert(int data) {
        insertHelper(this->root, data);
    }

    // Ağacın yüksekliğini hesaplama fonksiyonu
    int height() {
        return heightHelper(this->root);
    }

    // Ağacın düğüm değerlerinin toplamını hesaplama fonksiyonu
    int sum() {
        return sumHelper(this->root);
    }

    // Ağacı postorder sırada yazdırma fonksiyonu
    void printPostorder() {
        printPostorderHelper(this->root);
        cout << endl;
    }
};

// Ana fonksiyon
int main() {
    // Sayilar.txt dosyasını okumak için bir akış nesnesi oluştur
    ifstream file("Sayilar.txt");

    // Eğer dosya açılamazsa, hata mesajı ver ve programı bitir
    if (!file.is_open()) {
        cerr << "Dosya açılamadı!" << endl;
        return -1;
    }

    // Dosyadaki her satır için
    string line;
    while (getline(file, line)) {
        // Satırı boşluklara göre böl ve sayıları bir diziye kaydet
        const int MAX_NUMBERS = 100; // Maksimum sayı adedi
        int numbers[MAX_NUMBERS];
        int count = 0; // Sayı adedi
        istringstream iss(line);
        int number;
        while (iss >> number) {
            if (count < MAX_NUMBERS) {
                numbers[count++] = number;
            }
        }

        // Sayıları yığıta kaydetme işlemi için bir yığın (stack) oluştur
        const int MAX_STACK_SIZE = 100; // Maksimum yığın boyutu
        int stack[MAX_STACK_SIZE]; // Yığını tutan dizi
        int stackSize = 0; // Yığının mevcut boyutu

        // Dizideki her sayı için
        for (int i = 0; i < count; i++) {
            // Yığına ekle
            stack[stackSize++] = numbers[i];
        }

        // Yığıttaki sayıları ikili arama ağacına ekleme işlemi
        BST tree;
        for (int i = 0; i < stackSize; i++) {
            tree.insert(stack[i]);
        }

        // Ağacın postorder sırada yazdırılması
        tree.printPostorder();

        // 10 milisaniye bekle
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    // Dosyayı kapat
    file.close();

    // Programı bitir
    return 0;
}
