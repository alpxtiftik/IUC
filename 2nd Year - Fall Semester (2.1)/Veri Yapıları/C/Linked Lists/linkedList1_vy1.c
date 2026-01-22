#include <stdio.h>
#include <stdlib.h>

// Node yapısını tanımlıyoruz. Her node bir tamsayı değer (x) tutar ve bir sonraki node'u işaret eder.
struct node {
    int x; // node içerisindeki veri (data)
    struct node* next; // bir sonraki node'a işaret eden pointer
};

int main(){
    // İlk node için bellek ayırıyoruz. root, listenin başlangıcını işaret eder.
    struct node* root = (struct node*)malloc(sizeof(struct node));
    root->x = 10; // İlk node'un x değerini 10 yapıyoruz.
    
    // İkinci node için bellek ayırıyoruz ve root'un next pointer'ını bu yeni node'a bağlayarak zinciri oluşturuyoruz.
    root->next = (struct node*)malloc(sizeof(struct node));
    root->next->x = 20; // İkinci node'un x değerini 20 yapıyoruz.
    
    // Üçüncü node için de aynı şekilde bellek ayırıyoruz ve ikinci node'un next pointer'ını üçüncü node'a bağlıyoruz.
    root->next->next = (struct node*)malloc(sizeof(struct node));
    root->next->next->x = 30; // Üçüncü node'un x değerini 30 yapıyoruz.
    
    root->next->next->next = NULL;//Son linked list elemanının next'i null.

    // Üstteki işlemlerde sürekli "next" kullanarak pointer'ları güncellemek zahmetli olabilir.
    // Bu yüzden iter adında bir pointer kullanacağız. Bu pointer, root'un gösterdiği yeri gösterecek.
    struct node * iter = root; // iter ilk başta root'u yani birinci node'u gösterir.
    
    // Şimdi iter pointer'ını bir sonraki node'a ilerletiyoruz.
    iter = iter->next; // iter artık ikinci node'u gösteriyor.
    
    // iter'i tekrar bir sonraki node'a ilerletiyoruz.
    iter = iter->next; // iter artık üçüncü node'u gösteriyor.
    
    // Bu şekilde sürekli "next" yazmak yerine "iter" ile daha kısa ve okunabilir bir yapı elde ettik.
}