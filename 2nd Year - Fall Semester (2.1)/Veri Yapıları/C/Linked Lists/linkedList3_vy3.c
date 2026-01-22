#include <stdio.h>
#include <stdlib.h>

// Node yapısını tanımlıyoruz. Her node, bir tamsayı veri ve bir sonraki node'u işaret eden bir pointer içerir.
struct node {
    int x;              // Node'un tuttuğu veri
    struct node* next;  // Bir sonraki node'a işaret eden pointer
};

// Bağlı listenin tüm elemanlarını yazdıran fonksiyon
void bastir(struct node * r){
    int i = 1;
    while(r != NULL){ // Listenin sonuna kadar ilerliyoruz (r NULL olana kadar)
        printf("%d. Eleman: %d\n", i, r->x); // Her bir elemanı ekrana yazdırıyoruz
        r = r->next; // Bir sonraki node'a geçiyoruz
        i++;
    }
}

// Listenin sonuna yeni bir eleman ekleyen fonksiyon
void ekleSona(struct node *r, int x){
    // Listenin sonuna kadar ilerliyoruz
    while(r->next != NULL){
        r = r->next;
    }
    // Yeni node için bellek ayırıyoruz
    r->next = (struct node*)malloc(sizeof(struct node));
    r->next->x = x;    // Yeni node'un değerini ayarlıyoruz
    r->next->next = NULL; // Yeni node'u listenin sonuna eklediğimiz için next'i NULL yapıyoruz
}

// Sıralı ekleme yapan fonksiyon. Root değişebilir, bu yüzden geri dönüş tipi 'node*'.
struct node* ekleSirali(struct node * r, int x){
    // Eğer liste boşsa (root NULL ise)
    if (r == NULL){
        // Yeni node için bellek ayırıyoruz
        r = (struct node *)malloc(sizeof(struct node));
        r->next = NULL; // Yeni node'un next'i yok, çünkü tek eleman var
        r->x = x; // Node'un değerini ayarlıyoruz
        return r; // Yeni root'u geri döndürüyoruz
    }
    
    // Eğer eklenecek eleman, root'tan küçükse yeni eleman başa eklenecek
    if(r->x > x){ 
        struct node * temp = (struct node *)malloc(sizeof(struct node)); // Yeni node oluşturuluyor
        temp->x = x;  // Yeni node'un değerini atıyoruz
        temp->next = r; // Yeni node'un next'i eski root'a işaret ediyor
        return temp;    // Yeni root, eklenen node oluyor
    }

    // Listenin içinde uygun yere kadar ilerlemek için iter kullanıyoruz
    struct node * iter = r;
    while (iter->next != NULL && iter->next->x < x ){
        iter = iter->next; // Uygun konuma kadar ilerliyoruz
    }

    // Yeni node oluşturuluyor
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->next = iter->next; // Yeni node'un next'i, iter'in next'ine işaret ediyor (araya ekleme yapıyoruz)
    iter->next = temp; // Iter'in next'i yeni node oluyor
    temp->x = x; // Yeni node'un değerini ayarlıyoruz
    return r; // Değişen root'u geri döndürüyoruz
}


int main(){
    struct node* root = NULL; // Başlangıçta root NULL olarak ayarlanıyor (boş liste)
    
    // Listeye sıralı elemanlar ekleniyor
    root = ekleSirali(root, 400); // 400 ekleniyor
    root = ekleSirali(root, 40);  // 40 ekleniyor (sıralı ekleme)
    
    // Tüm elemanlar ekrana yazdırılıyor
    bastir(root); 
}