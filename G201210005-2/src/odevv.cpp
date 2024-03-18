/**
 * odevv
 * txt dosyası içerisindeki sayıları gruplandırdıktan sonra kullanıcıdan indeks alıp yerlerini değiştiriyor ve  ortalama toplamı alıyor ust ve alt şeklinde ekranda yazdırıyor
 * 2.ogretim A grubu 
 * odev 1 
 * 27.07.2023
 * Tugba Dirmenci / tugba.dirmenci@ogr.sakarya.edu.tr
 */


#include <iostream>
#include <fstream> 
#include <iomanip>
#include "linkedlist.hpp"

using namespace std;

int main() 
{
    string dosya_adı = "Sayilar.txt"; //txt dosyasını okuyor.
    ifstream dosya(dosya_adı);
    if (!dosya.is_open()) {
        cout << "Dosya açılamadı!" << endl;
        return 1; // acilamadigi durumda 1 döndürüyor.
    }

    int satir_sayisi = 0; // dosyada kaç satır olduğnu tutmak için değişken
    string satir;
    while (getline(dosya, satir)) {
        satir_sayisi++; //satır sayısı hesapla
    }

    dosya.clear(); //dosya akış nesnesi temizler
    dosya.seekg(0); // dosya işaretçisini başa sıfırlar

    Node** konumA = new Node*[satir_sayisi]; // yukarı yönlü bağıl listelerin başlangıç düğüm pointerı 
    Node** konumB = new Node*[satir_sayisi]; // aşağı yönlü listelerin başlangıç düğüm pointerı 

    int index = 0; 
    while (getline(dosya, satir)) {
        Node* downHead = nullptr; //aşağı yönlü liste başlangıç düğümü
        Node* upHead = nullptr;   // yukarı yönlü liste başlangıç düğümü 

        size_t pos = 0;
        while ((pos = satir.find_first_of("0123456789", pos)) != string::npos) {
            char onlar = satir[pos] - '0'; //onlar basamağı 
            char birler = satir[pos + 1] - '0'; //birler basamağı

            Node* newNode = new Node(birler); // aşağı yönlü bağıl listeye eklenecek düğüm 
            newNode->next = downHead;
            downHead = newNode;

            Node* newNode2 = new Node(onlar); // yukarı yönlü listeye eklenecek düğüm
            newNode2->next = upHead;
            upHead = newNode2;

            pos += 2;
        }

        konumA[index] = upHead; // yukarı yönlü b.listenin başlangıç düğümünü dizide sakla 
        konumB[index] = downHead; //aşağı yönlü b.listenin başlangıç düğümünü dizide sakla 
        index++;
    }

    dosya.close();

    int i, j;
    cout << "Konum A: ";
     cin >> i; //kullanıcıdan indeks al 
    cout<<"Konum B: ";
    cin >>j; // kullanıcıdan indeks al 

    if (i < 0 || i >= satir_sayisi || j < 0 || j >= satir_sayisi) {
        cout << "Geçersiz indeks!" << endl;
        return 1; // hatalı indeks durumunda bir döndür
    }

    Node* temp = konumA[i]; // yukarı yönlü b.listeleri değiştirmek için geçici pointer ata
    konumA[i] = konumB[j];
    konumB[j] = temp;

    printAllDownwardLists(konumB, satir_sayisi); //aşağı yönlü bağıl listeleri yazdır 
    printAllUpwardLists(konumA, satir_sayisi); //yukarı yönlü bağıl listeleri yazdır 

    calculateAverage(konumA, konumB, satir_sayisi); // ortalama hesapla ve yazdır

    Node* temp2; 
    for (int k = 0; k < satir_sayisi; k++) {
        while (konumA[k] != nullptr) {
            temp2 = konumA[k]; // geçici düğüm işaretçisi ile konumA[k]yı ona ata 
            konumA[k] = konumA[k]->next; // düğümü ilerlet 
            delete temp2; //geçici düğümü sil dinamik bellekten önceki düğümü temizler
        }
        while (konumB[k] != nullptr) {
            temp2 = konumB[k]; // üstteki kısmı konumB[k]için yapar 
            konumB[k] = konumB[k]->next;
            delete temp2;
        }
    }

    delete[] konumA;
    delete[] konumB; // bellek temizler 

    return 0;
}
