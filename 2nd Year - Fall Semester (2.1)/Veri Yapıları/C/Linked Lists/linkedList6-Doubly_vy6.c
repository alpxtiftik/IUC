#include <stdio.h>
#include <stdlib.h>

// Node yapısını tanımlıyoruz. Her düğüm (node), bir int değer (x), bir sonraki düğüme işaretçi (next) ve önceki düğüme işaretçi (prev) içerir.
struct node {
    int x;
    struct node* next;
    struct node* prev; 
};

// Listeyi baştan sona yazdıran fonksiyon.
// r, listenin kök (root) düğümünü gösterir.
void bastir(struct node * r){
    int i = 1;
    // Listenin sonuna kadar ilerleyip her düğümün değerini yazdırır.
    while(r != NULL){
        printf("%d. Eleman: %d\n", i, r->x);
        r = r->next;
        i++;
    }
}

// Listenin sonuna eleman ekleyen fonksiyon.
// r, listenin kök düğümünü gösterir ve x, eklenmek istenen değerdir.
void ekleSona(struct node *r, int x){
    // Listenin sonuna kadar ilerler.
    while(r->next != NULL){
        r = r->next;
    }
    // Yeni düğüm oluşturup, listenin sonuna ekler.
    r->next = (struct node*)malloc(sizeof(struct node));
    r->next->x = x;
    r->next->next = NULL;
    r->next->prev = r; // prev işaretçisi de önceki düğümü işaret eder.
}

// Sıralı ekleme fonksiyonu.
// Eğer liste boşsa, yeni bir düğüm oluşturulur.
// Eğer eklenecek değer mevcut düğümlerden küçükse başa eklenir.
// Diğer durumlarda sıralı bir şekilde uygun pozisyona eklenir.
struct node* ekleSirali(struct node * r, int x){
    // Eğer liste boşsa, yeni bir düğüm oluşturup root olarak geri döner.
    if (r == NULL){
        r = (struct node *)malloc(sizeof(struct node));
        r->next = NULL;
        r->prev = NULL;
        r->x = x;
        return r;
    }
    
    // Eğer eklenecek değer root'tan küçükse, başa eklenir.
    if(r->x > x){ 
        struct node * temp = (struct node *)malloc(sizeof(struct node));
        temp->x = x;
        temp->next = r;
        r->prev = temp;
        temp->prev = NULL;
        return temp;
    }

    // Yeni düğümün nereye ekleneceğini bulmak için listeyi dolaşır.
    struct node * iter = r;
    while (iter->next != NULL && iter->next->x < x ){
        iter = iter->next;
    }

    // Yeni düğüm oluşturulup uygun pozisyona eklenir.
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->next = iter->next;
    iter->next = temp;
    temp -> prev = iter;
    if(temp->next != NULL){ // Eğer sona eklenmiyorsa
        temp->next->prev = temp;    
    }
    temp->x = x;
    return r;
}

// Listedeki bir elemanı silen fonksiyon.
// Eğer silinecek eleman root ise root güncellenir.
// Silinen düğümün önceki ve sonraki düğümleri arasındaki bağlantılar düzeltilir.
struct node * sil(struct node *r, int x){
    struct node * temp;
    struct node * iter = r;
    
    // Eğer silinecek eleman root ise, root güncellenir ve eski root silinir.
    if(r->x == x){
        temp = r;
        r = r->next;
        if(r != NULL){
            r->prev = NULL; // Yeni root'un prev işaretçisi NULL yapılır.
        }
        free(temp);
        return r;
    }

    // Listede elemanı arar.
    while(iter->next != NULL && iter->next->x != x){
        iter = iter->next;
    }
  
    // Eğer eleman bulunamazsa bir mesaj verir.
    if (iter->next == NULL){
        printf("Sayi bulunamadi.\n");
        return r;
    }

    // Eleman bulunduysa silme işlemi yapılır.
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    if(iter->next != NULL){
        iter->next->prev = iter; // Sonraki düğümün prev işaretçisi güncellenir.
    }
    return r;
}

int main(){
    struct node* root = NULL; // Başlangıçta boş bir liste.
    
    // Listeye sıralı elemanlar ekleniyor.
    root = ekleSirali(root, 400); 
    root = ekleSirali(root, 40);  
    root = ekleSirali(root, 50);
    root = ekleSirali(root, 3);
    
    // Tüm listeyi yazdırır.
    bastir(root); 

    printf("\n");

    // 40 değerini listeden siler ve ardından listeyi tekrar yazdırır.
    root = sil(root, 40);
    bastir(root);
}