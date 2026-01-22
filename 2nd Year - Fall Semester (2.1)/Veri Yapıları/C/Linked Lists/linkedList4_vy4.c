#include <stdio.h>
#include <stdlib.h>

// Node yapısı tanımlanıyor. Her node, bir tamsayı veri ve bir sonraki node'u işaret eden pointer içeriyor.
struct node {
    int x;              // Node'un tuttuğu veri
    struct node* next;  // Bir sonraki node'u işaret eden pointer
};

// Bağlı listedeki tüm elemanları yazdıran fonksiyon
void bastir(struct node * r){
    int i = 1;
    // Liste sonuna kadar gidiyoruz (NULL olana kadar)
    while(r != NULL){
        // Elemanları ekrana yazdırıyoruz
        printf("%d. Eleman: %d\n", i, r->x);
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
    // Yeni bir node oluşturuluyor ve listeye ekleniyor
    r->next = (struct node*)malloc(sizeof(struct node));
    r->next->x = x;    // Yeni node'un değerini atıyoruz
    r->next->next = NULL; // Yeni node son eleman olduğu için next'i NULL
}

// Sıralı ekleme yapan fonksiyon, geri dönüş tipi 'struct node*' çünkü root değişebilir
struct node* ekleSirali(struct node * r, int x){
    // Eğer liste boşsa (root NULL ise)
    if (r == NULL){
        r = (struct node *)malloc(sizeof(struct node)); // Yeni node için bellek ayırıyoruz
        r->next = NULL;  // Tek eleman olduğu için next'i NULL
        r->x = x;  // Node'un değerini ayarlıyoruz
        return r;  // Yeni root'u geri döndürüyoruz
    }
    
    // Eğer yeni eklenen eleman root'tan küçükse, root'u güncelliyoruz
    if(r->x > x){ 
        struct node * temp = (struct node *)malloc(sizeof(struct node)); // Yeni node için bellek ayırıyoruz
        temp->x = x;  // Yeni node'un değerini atıyoruz
        temp->next = r; // Yeni node'un next'i eski root olacak
        return temp;    // Yeni root artık eklenen node
    }

    // Listenin içinde uygun konuma kadar ilerlemek için iter kullanılıyor
    struct node * iter = r;
    while (iter->next != NULL && iter->next->x < x ){
        iter = iter->next; // Uygun konuma gelene kadar iter ilerliyor
    }

    // Uygun yere yeni node ekleniyor
    struct node * temp = (struct node *)malloc(sizeof(struct node));
    temp->next = iter->next; // Yeni node'un next'i, iter'in next'ine bağlanıyor
    iter->next = temp;  // Iter'in next'i artık yeni node
    temp->x = x;  // Yeni node'un değeri atanıyor
    return r;  // Değişen root'u geri döndürüyoruz
}

// Verilen değere sahip node'u silen fonksiyon, geri dönüş tipi 'struct node*' çünkü root değişebilir
struct node * sil(struct node *r, int x){
    struct node * temp;  // Silinecek node'u geçici olarak tutacak pointer
    struct node * iter = r;  // Listede gezinmek için iter kullanıyoruz
    
    // Eğer root silinmek isteniyorsa, root'u güncellememiz gerekiyor
    if(r->x == x){
        temp = r;  // Eski root'u temp'e atıyoruz
        r = r->next;  // Root'u bir sonraki node yapıyoruz
        free(temp);  // Eski root'u serbest bırakıyoruz (bellekten siliyoruz)
        return r;  // Yeni root'u geri döndürüyoruz
    }

    // Silinmek istenen değeri bulmak için listenin içinde ilerliyoruz
    while(iter->next != NULL && iter->next->x != x){
        iter = iter->next;
    }

    // Eğer silinmek istenen eleman bulunamazsa
    if (iter->next == NULL){
        printf("Sayi bulunamadi.\n");  // Hata mesajı basılıyor
        return r;  // Root geri döndürülüyor (değişiklik yok)
    }

    // Silinmek istenen node bulunursa
    temp = iter->next;  // Silinecek node'u temp'e atıyoruz
    iter->next = iter->next->next;  // Node'u listeden çıkarıyoruz
    free(temp);  // Silinen node'u serbest bırakıyoruz
    return r;  // Yeni root'u geri döndürüyoruz
}

int main(){
    struct node* root = NULL;  // Başlangıçta root NULL (boş liste)
    
    // Listeye sıralı elemanlar ekleniyor
    root = ekleSirali(root, 400); 
    root = ekleSirali(root, 40);  
    root = ekleSirali(root, 50);
    
    // Listenin elemanları yazdırılıyor
    bastir(root); 

    printf("\n");

    // Eleman silme işlemi yapılıyor ve yeni liste yazdırılıyor
    root = sil(root, 40);
    bastir(root);
}