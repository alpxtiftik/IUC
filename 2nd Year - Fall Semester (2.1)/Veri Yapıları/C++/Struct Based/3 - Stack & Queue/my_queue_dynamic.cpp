#include <iostream>
using namespace std; 

#define SIZE 10 // Bu makro kullanılmıyor ama gerekirse dinamik bir yapı için kullanılabilir

// Node yapısı
struct node {
    int data; 
    struct node * next; 
};

// Kuyruk yapısı
struct queue{
    int cnt; // Kuyruktaki eleman sayısı
    struct node * rear; // Son node
    struct node * front; // İlk node
};

// Kuyruğu başlatma fonksiyonu
void initialize(queue * q) {
    q->cnt = 0; 
    q->rear = q->front = NULL;
}

// Kuyruğun boş olup olmadığını kontrol eden fonksiyon
bool isEmpty(queue * q) {
    return (q->cnt == 0); // Eleman sayısı sıfırsa kuyruk boştur.
}

// Kuyruğa eleman ekleme fonksiyonu
void enqueue(queue * q, int key) {
    struct node * add = new node; // Yeni düğüm oluşturuluyor
    add->data = key;
    add->next = NULL; // Yeni düğüm son düğüm olacak, bu yüzden next NULL

    if (isEmpty(q)) { // Kuyruk boşsa
        q->front = q->rear = add; // İlk eleman
        cout << "Queue'deki ilk node olusturuldu" << endl;
    } else { // En az bir eleman var
        q->rear->next = add; // Eski son düğümün next'ine yeni düğüm atanıyor
        q->rear = add; // Rear güncelleniyor
    }
    q->cnt++; // Eleman sayısı arttırılıyor
    cout << "Queue'ye node eklendi" << endl;
}

// Kuyruktan eleman çıkarma fonksiyonu
void dequeue(queue * q) {
    if (isEmpty(q)) {
        cout << "Kuyruk boş, silinecek düğüm yok." << endl;
    } else if (q->cnt == 1) { // Tek düğüm durumu
        cout << "Queue'nin en onundeki node silindi. Tek elemani oldugu icin Queue bos kaldi." << endl;
        delete q->front; // İlk düğüm siliniyor
        q->front = NULL;
        q->rear = NULL;
        q->cnt--; // Eleman sayısı azaltılıyor
    } else { // Birden fazla düğüm durumu
        cout << "Queue'nin en onundeki node silindi." << endl;
        struct node * temp = q->front; // İlk düğüm geçici bir değişkende saklanıyor
        q->front = q->front->next; // Front bir sonraki düğüme güncelleniyor
        delete temp; // Eski front düğümü siliniyor
        q->cnt--; // Eleman sayısı azaltılıyor
    }
}

// Kuyruktaki elemanları yazdırma fonksiyonu
void print(queue * q) {
    if (isEmpty(q)) {
        cout << "Queue bos." << endl;
    } else {
        struct node * iter = q->front; // Front'tan başlayarak yazdırma
        while (iter != NULL) {
            cout << iter->data << " -> ";
            iter = iter->next; // Sonraki düğüme geç
        }
        cout << "NULL" << endl; // Kuyruğun sonunu belirtmek için
    }
}

void destroy(queue *q) {// Bu fonksiyon, kuyrukta kalan tüm düğümleri serbest bırakır ve bellek sızıntısını önler.
    while (!isEmpty(q)) {
        dequeue(q); // Bütün düğümleri sırayla sil
    }
    cout << "Kuyruk tamamen temizlendi." << endl;
}


// Ana fonksiyon
int main() {
    struct queue qu;
    initialize(&qu);
    
    int sayi, secim;
    
    while (1) {
        cout << endl << "QUEUE Uygulaması" << endl;
        cout << "1-- Enqueue" << endl << "2-- Dequeue" << endl << "3-- Print" << endl;
        cout << "4-- Cikis" << endl; 
        
        cin >> secim;

        switch (secim) {
            case 1: 
                cout << "Sayi girin: "; 
                cin >> sayi;
                enqueue(&qu, sayi);
                break;
                
            case 2: 
                dequeue(&qu);
                break;
                
            case 3: 
                print(&qu);
                break;

            case 4: 
                destroy(&qu); // Kuyruktaki tüm düğümleri serbest bırak.
                return 0; // Programdan çık.
                
            default:
                cout << "Gecersiz secim, tekrar deneyin." << endl;
        }
    }
}
