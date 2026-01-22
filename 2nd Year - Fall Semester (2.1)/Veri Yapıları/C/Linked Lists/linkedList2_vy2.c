#include <stdio.h>
#include <stdlib.h>

// Node yapısını tanımlıyoruz. Her node bir tamsayı (x) tutar ve bir sonraki node'u işaret eden bir pointer'a sahiptir.
struct node {
    int x; // node içerisindeki veri (data)
    struct node* next; // bir sonraki node'a işaret eden pointer
};

// Linked list'in elemanlarını ekrana yazdıran fonksiyon
void bastir(struct node * r) {
    int i = 1; // Eleman sayısını izlemek için sayaç
    // r null olmadıkça (yani listenin sonuna ulaşmadıkça)
    while (r != NULL) {
        printf("%d. Eleman: %d\n", i, r->x); // Elemanın sırası ve değeri yazdırılıyor
        r = r->next; // Sonraki node'a geçiliyor
        i++; // Sayaç bir artırılıyor
    }
}

// Linked list'e yeni bir eleman ekleyen fonksiyon
void ekle(struct node * r, int x) {
    // Son düğüme ulaşana kadar döngü devam ediyor
    while (r->next != NULL) {
        r = r->next; // r'yi bir sonraki node'a geçiriyoruz
    }
    // Son düğümün yanına yeni bir node ekliyoruz
    r->next = (struct node*)malloc(sizeof(struct node)); // Yeni node için bellek ayırıyoruz
    r->next->x = x; // Yeni node'un x değerini atıyoruz
    r->next->next = NULL; // Yeni node'un next pointer'ını NULL olarak ayarlıyoruz
}

int main() {
    // Root (kök) node için bellek ayırıyoruz ve başlangıç değerlerini atıyoruz
    struct node* root = (struct node*)malloc(sizeof(struct node)); // Kök node için bellek ayır
    root->next = NULL; // Kök node'un next pointer'ını NULL yap
    root->x = 10; // Kök node'un x değerini 10 olarak ayarla
    
    // 0'dan 4'e kadar olan değerleri (0, 10, 20, 30, 40) linked list'e ekliyoruz
    for (int i = 0; i < 5; i++) {
        ekle(root, i * 10); // her döngüde yeni bir eleman ekleniyor
    }
    
    // Linked list'in elemanlarını ekrana yazdır
    bastir(root); // Listenin içeriğini yazdıran fonksiyon çağrılıyor
}