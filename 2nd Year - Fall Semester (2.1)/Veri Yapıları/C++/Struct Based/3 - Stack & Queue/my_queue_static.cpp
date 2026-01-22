#include <iostream> 
using namespace std;

#define SIZE 10  // Kuyruk için maksimum boyut.

struct queue {
    int data[SIZE]; // Verilerin saklanacağı dizi.
    int cnt;        // Kuyrukta kaç eleman olduğunu gösteren sayaç.
    int front;      // Kuyruğun başını (ilk elemanı) gösteren indeks.
    int rear;       // Kuyruğun sonunu (son elemanı) gösteren indeks.
};

// Kuyruğu başlatan fonksiyon.
void initialize(queue* q) {
    q->cnt = 0;  // Kuyruk başlangıçta boş.
    q->front = 0;
    q->rear = -1;
}

// Kuyruğun dolu olup olmadığını kontrol eden fonksiyon.
bool isFull(queue* q) {
    return (q->cnt == SIZE);
}

// Kuyruğun boş olup olmadığını kontrol eden fonksiyon.
bool isEmpty(queue* q) {
    return (q->cnt == 0);
}

// Kuyruğa eleman ekleme fonksiyonu.
void enqueue(queue* q, int key) {
    if (isFull(q)) {
        cout << "Queue dolu." << endl;
        return;
    }
    q->rear = (q->rear + 1) % SIZE; // Dairesel kuyruk mantığı.
    q->data[q->rear] = key;
    q->cnt++;
    cout << "Eleman eklendi: " << key << endl;
}

// Kuyruktan eleman çıkarma fonksiyonu.
void dequeue(queue* q) {
    if (isEmpty(q)) {
        cout << "Queue bos." << endl;
        return;
    }
    cout << "Eleman cikarildi: " << q->data[q->front] << endl;
    q->front = (q->front + 1) % SIZE; // Dairesel kuyruk mantığı.
    q->cnt--;
}

// Kuyruktaki elemanları yazdıran fonksiyon.
void print(queue* q) {
    if (isEmpty(q)) {
        cout << "Queue bos." << endl;
        return;
    }
    cout << "Queue: ";
    for (int i = 0; i < q->cnt; i++) {
        int index = (q->front + i) % SIZE;
        cout << q->data[index] << " -> ";
    }
    cout << "NULL" << endl;
}

// Ana fonksiyon.
int main() {
    queue qu;
    initialize(&qu);

    int sayi, secim;

    while (true) {
        cout << "\nQUEUE Uygulamasi" << endl;
        cout << "1-- Enqueue\n2-- Dequeue\n3-- Print\nSecim: ";
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
            default:
                cout << "Gecersiz secim!" << endl;
        }
    }
    return 0;
}
