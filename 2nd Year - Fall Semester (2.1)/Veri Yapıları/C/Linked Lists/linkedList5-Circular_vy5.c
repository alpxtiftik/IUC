#include <stdio.h>
#include <stdlib.h>

// Dairesel bağlı liste için düğüm yapısı tanımlanıyor
struct node {
    int x;              // Düğümün tuttuğu veri
    struct node* next;  // Bir sonraki düğümü işaret eden pointer (dairesel olduğu için son düğüm ilk düğümü işaret eder)
};

// Bağlı listedeki tüm elemanları ekrana yazdıran fonksiyon
void bastir(struct node * r){
    struct node * iter; // Liste üzerinde dolaşmak için iter değişkeni
    int i = 1; // Eleman sırasını tutmak için sayaç
    
    iter = r; // iter başlangıç olarak root'u (ilk elemanı) işaret edecek
    printf("%d. Eleman: %d\n", i, iter->x); // İlk elemanı yazdır
    
    iter = iter->next; // iter'i bir sonraki düğüme ilerlet
    
    // iter tekrar root'a (ilk elemana) gelene kadar listeyi döngüde yazdır
    while(iter != r){
        i++;
        printf("%d. Eleman: %d\n", i, iter->x); // Diğer elemanları yazdır
        iter = iter->next; // Bir sonraki düğüme geç
    }
}

// Listenin sonuna yeni bir eleman ekleyen fonksiyon
void ekleSona(struct node *r, int x){
    struct node * iter = r; // iter başlangıç olarak root'u işaret edecek
    
    // iter'i listenin sonuna kadar ilerlet (son düğüm, root'u işaret eder)
    while(iter->next != r){
        iter = iter->next; // Bir sonraki düğüme geç
    }
    
    // Yeni bir düğüm oluştur ve sonuna ekle
    iter->next = (struct node*)malloc(sizeof(struct node)); // Yeni düğüm için bellek tahsis et
    iter->next->x = x; // Yeni düğümün değerini ata
    iter->next->next = r; // Yeni düğümün next'i, root'u (ilk düğümü) işaret edecek, dairesellik korunacak
}

// Listeye sıralı şekilde eleman ekleyen fonksiyon
struct node* ekleSirali(struct node * r, int x){
    // Eğer liste boşsa (root yoksa)
    if (r == NULL){
        r = (struct node *)malloc(sizeof(struct node)); // Yeni düğüm için bellek tahsis et
        r->next = r; // Tek eleman olduğu için kendisini işaret eder
        r->x = x; // Elemanın değerini ata
        return r; // Yeni root'u döndür
    }
    
    // Yeni eklenen eleman root'tan küçükse, root değişecek
    if(r->x > x){ 
        struct node * temp = (struct node *)malloc(sizeof(struct node)); // Yeni düğüm için bellek tahsis et
        temp->x = x; // Yeni elemanın değerini ata
        temp->next = r; // Yeni elemanın next'i eski root'u işaret edecek
        struct node * iter = r; // Listenin sonuna gitmek için iter oluştur
        while(iter->next != r){
            iter = iter->next; // Son düğüme kadar ilerle
        }
        iter->next = temp; // Son düğümün next'i yeni root olacak
        return temp; // Yeni root olarak temp'i döndür
    }

    // Diğer durumlar için uygun yere kadar ilerleyip yeni düğümü ekliyoruz
    struct node * iter = r;
    while (iter->next != r && iter->next->x < x ){
        iter = iter->next; // Uygun pozisyona kadar iter'i ilerlet
    }

    // Yeni düğüm oluşturulup uygun yere ekleniyor
    struct node * temp = (struct node *)malloc(sizeof(struct node)); // Yeni düğüm için bellek tahsis et
    temp->next = iter->next; // Yeni düğümün next'i iter'in next'ine bağlanıyor
    iter->next = temp; // iter'in next'i artık yeni düğümü işaret edecek
    temp->x = x; // Yeni düğümün değeri atanıyor
    return r; // Root'u geri döndür (değişmedi)
}

// Verilen değere sahip düğümü silen fonksiyon
struct node * sil(struct node *r, int x){
    struct node * temp; // Silinecek düğümü geçici olarak tutacak pointer
    struct node * iter = r; // Liste üzerinde gezinmek için iter
    
    // Eğer silinmek istenen düğüm root ise (ilk düğüm)
    if(r->x == x){
        // Listenin sonuna kadar ilerliyoruz
        while(iter->next != r){
            iter = iter -> next; 
        }
        iter -> next = r-> next; // Son düğümün next'ini yeni root'a bağlıyoruz
        free(r); // Eski root'u bellekten siliyoruz
        return iter -> next ; // Yeni root'u döndürüyoruz
    }

    // Silinmek istenen değeri bulana kadar ilerliyoruz
    while(iter->next != r && iter->next->x != x){
        iter = iter->next; // İlerleme
    }

    // Eğer eleman bulunamazsa
    if (iter->next == r){
        printf("Sayi bulunamadi.\n");
        return r; // Root'u döndür (değişiklik olmadı)
    }

    // Eleman bulunduysa, silme işlemi yapılıyor
    temp = iter->next; // Silinecek düğümü temp'e atıyoruz
    iter->next = iter->next->next; // Düğümü listeden çıkarıyoruz
    free(temp); // Silinen düğümü bellekten siliyoruz
    return r; // Root'u döndürüyoruz
}

int main(){
    struct node* root = NULL; // Başlangıçta boş liste (root NULL)
    
    // Listeye sıralı elemanlar ekleniyor
    root = ekleSirali(root, 400); 
    root = ekleSirali(root, 50);
    root = ekleSirali(root, 4);

    // Liste yazdırılıyor
    bastir(root);
    
    // Bir eleman siliniyor
    root = sil(root, 400);

    // Güncellenmiş liste tekrar yazdırılıyor
    bastir(root);
}
