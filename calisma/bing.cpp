// Gerekli kütüphaneleri dahil edin
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
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
        Node* insertHelper(Node* node, int data) {
            // Eğer ağaç boşsa, yeni düğümü kök yap
            if (node == NULL) {
                return new Node(data);
            }

            // Eğer eklenecek değer düğümün değerinden küçükse, sol alt ağaca ekle
            if (data < node->data) {
                node->left = insertHelper(node->left, data);
            }

            // Eğer eklenecek değer düğümün değerinden büyükse, sağ alt ağaca ekle
            else if (data > node->data) {
                node->right = insertHelper(node->right, data);
            }

            // Eğer eklenecek değer düğümün değerine eşitse, eklemeyi yapma (aynı değerleri engelle)

            // Düğümü geri döndür
            return node;
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
            this->root = insertHelper(this->root, data);
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
        // Satırı boşluklara göre böl ve sayıları bir vektöre kaydet
        vector<int> numbers;
        int number;
        istringstream iss(line);
        while (iss >> number) {
            numbers.push_back(number);
        }

        // Sayıları yığıtlara bölme işlemi için bir yığıt vektörü oluştur
        vector<stack<int> >stacks;

        // Vektördeki her sayı için
        for (int i = 0; i < numbers.size(); i++) {
            // Eğer yığıt vektörü boşsa, yeni bir yığıt oluştur ve sayıyı ekle
            if (stacks.empty()) {
                stack<int> s;
                s.push(numbers[i]);
                stacks.push_back(s);
            }
            else {
                // Eğer sayı çift ve o an işlem yapılan yığıttan çıkmak üzere olan sayıdan büyükse, yeni bir yığıta ekle
                if (numbers[i] % 2 == 0 && numbers[i] > stacks.back().top()) {
                    stack<int> s;
                    s.push(numbers[i]);
                    stacks.push_back(s);
                }
                else {
                    // Değilse, mevcut yığıta ekle
                    stacks.back().push(numbers[i]);
                }
            }
        }

        // Yığıtları ikili arama ağaçlarına dönüştürme işlemi için bir BST vektörü oluştur
        vector<BST> trees;

        // Yığıt vektöründeki her yığıt için
        for (int i = 0; i < stacks.size(); i++) {
            // Yeni bir BST oluştur
            BST tree;

            // Yığıttaki her sayıyı BST'ye ekle (aynı değerleri engelle)
            while (!stacks[i].empty()) {
                tree.insert(stacks[i].top());
                stacks[i].pop();
            }

            // BST'yi BST vektörüne ekle
            trees.push_back(tree);
        }

        // BST vektöründeki en büyük yüksekliğe sahip ağacı bulma işlemi için değişkenler tanımla
        int maxHeight = 0; // En büyük yükseklik değeri
        int maxSum = 0; // En büyük toplam değeri
        int maxIndex = 0; // En büyük yüksekliğe sahip ağacın indeksi

        // BST vektöründeki her ağaç için
        for (int i = 0; i < trees.size(); i++) {
            // Ağacın yüksekliğini ve toplamını hesapla
            int height = trees[i].height();
            int sum = trees[i].sum();

            // Eğer ağacın yüksekliği en büyük yükseklikten büyükse, en büyük yüksekliği, toplamı ve indeksi güncelle
            if (height > maxHeight) {
                maxHeight = height;
                maxSum = sum;
                maxIndex = i;
            }

            // Eğer ağacın yüksekliği en büyük yüksekliğe eşitse, toplam değerlerini karşılaştır
            else if (height == maxHeight) {
                // Eğer ağacın toplamı en büyük toplamdan büyükse, en büyük toplamı ve indeksi güncelle
                if (sum > maxSum) {
                    maxSum = sum;
                    maxIndex = i;
                }
                // Eğer ağacın toplamı en büyük toplama eşitse, önce oluşturulan ağacı seç (indeksi değiştirme)
            }
        }

        // En büyük yüksekliğe sahip ağacı postorder sırada yazdır
        trees[maxIndex].printPostorder();

        // 10 milisaniye bekle
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    // Dosyayı kapat
    file.close();

    // Programı bitir
    return 0;
}
