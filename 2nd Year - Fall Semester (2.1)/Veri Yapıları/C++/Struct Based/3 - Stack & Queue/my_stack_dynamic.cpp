#include <iostream>
using namespace std; 

#define SIZE 10 // Stack'in maksimum boyutunu sabitliyoruz.

struct node { // Stack'e eklenecek düğüm yapısı (linked list node'u).
    int data; // Düğümün tuttuğu veri.
    struct node * next; // Sonraki düğüme işaretçi.
};

struct stack {
    struct node * top = NULL; // Stack'in en üstteki düğümüne işaret eden pointer.
    int cnt = 0; // Stack'teki toplam düğüm (eleman) sayısı.
};

// Stack dolu mu diye kontrol eden fonksiyon.
// Stack'in maksimum kapasitesi olan SIZE ile eleman sayısını karşılaştırır.
bool isFull(stack * stc) {
    if(stc->cnt == SIZE) {
        return 1; // Stack doluysa true (1) döner.
    }
    else
        return 0; // Stack dolu değilse false (0) döner.
}

// Stack boş mu diye kontrol eden fonksiyon.
// Eğer eleman sayısı 0 ise, stack boştur.
bool isEmpty(stack * stc) {
    if(stc->cnt == 0) {
        return 1; // Stack boşsa true (1) döner.
    }
    else
        return 0; // Stack boş değilse false (0) döner.
}

// Stack'e yeni eleman ekleme fonksiyonu (push işlemi).
// Stack dolu değilse yeni bir düğüm ekler.
void push(stack * stc, int key) {
    struct node * element = new node; // Yeni düğüm oluşturulur.
    element->data = key; // Düğümün verisi atanır.
    if (isFull(stc)) { // Eğer stack doluysa
        cout << "Stack dolu." << endl;
    }
    else if (isEmpty(stc)) { // Eğer stack boşsa
        stc->top = element; // Yeni düğüm stack'in tepesine yerleştirilir.
        element->next = NULL; // Yeni düğümün sonraki işaretçisi boş olmalı (tek eleman).
        stc->cnt ++; // Eleman sayısı artırılır.
        cout << "Stack oluşturuldu, ilk düğüm eklendi" << endl;
    }
    else { // Stack'te zaten eleman varsa
        element->next = stc->top; // Yeni düğüm, eski top düğümünü gösterir.
        stc->top = element; // Yeni düğüm artık stack'in en üstündeki düğüm olur.
        stc->cnt ++; // Eleman sayısı artırılır.
        cout << "Düğüm eklendi" << endl;
    }
}

// Stack'ten eleman çıkarma fonksiyonu (pop işlemi).
// Eğer stack boş değilse, en üstteki düğüm çıkarılır.
void pop(stack * stc) {
    if (stc->cnt == 0) { // Eğer stack boşsa
        cout << "Stack boş" << endl;
    }
    else {
        struct node * temp; // Geçici bir işaretçi tanımlanır.
        temp = stc->top; // Stack'in en üst düğümü geçici işaretçiye atanır.
        stc->top = stc->top->next; // Stack'in en üstü bir alt düğüme kaydırılır.
        delete temp; // Eski en üst düğüm bellekten silinir.
        stc->cnt --; // Eleman sayısı azaltılır.
    }
}

// Stack'in en üstündeki elemanı gösterir.
void top(stack * stc) {
    if (stc->cnt == 0) { // Eğer stack boşsa
        cout << "Stack boş" << endl;
    }
    else {
        cout << "En üst değer: " << stc->top->data << endl; // En üstteki düğümün verisi yazdırılır.
    }
}

// Stack'teki tüm elemanları sırasıyla yazdıran fonksiyon.
void print(stack * stc) {
    if (stc->cnt == 0) { // Eğer stack boşsa
        cout << "Stack boş" << endl;
    }
    else {
        struct node * temp = stc->top; // Geçici işaretçi stack'in en üstünü gösterir.
        while(temp->next != NULL) { // Stack'in son düğümüne kadar gider.
            cout << temp->data << endl; // Her düğümün verisini yazdırır.
            temp = temp->next; // Sonraki düğüme geçer.
        }
        cout << temp->data << endl; // Son düğümün verisini yazdırır (while döngüsünden sonra).
    }
}

int main(){

}