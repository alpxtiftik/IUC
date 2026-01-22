#include <iostream>
#include <cstdlib>  // malloc ve free için gerekli
using namespace std;

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

// Listeyi yazdıran fonksiyon
void printList() {
    struct node *p = head;
    cout << "\n[";

    // Listenin başından itibaren dolaş ve elemanları yazdır
    while (p != NULL) {
        cout << " " << p->data << " ";
        p = p->next;
    }
    cout << "]";
}

// Başlangıca düğüm ekleme
void insertAtBegin(int data) {
    // Yeni düğüm için bellek ayır
    struct node *lk = (struct node *)malloc(sizeof(struct node));
    lk->data = data;

    // Yeni düğümün 'next' pointer'ını şu anki baş düğüme bağla
    lk->next = head;

    // Yeni düğümü baş düğüm yap
    head = lk;
}

// Listenin sonuna düğüm ekleme
void insertAtEnd(int data) {
    struct node *lk = (struct node *)malloc(sizeof(struct node));
    lk->data = data;
    lk->next = NULL;  // Yeni düğümün son düğüm olduğunu belirt

    // Eğer liste boşsa, yeni düğüm baş düğüm olur
    if (head == NULL) {
        head = lk;
        return;
    }

    // Son düğüme ulaşmak için listeyi tara
    struct node *linkedlist = head;
    while (linkedlist->next != NULL)
        linkedlist = linkedlist->next;

    // Son düğümün next pointer'ını yeni düğüme bağla
    linkedlist->next = lk;
}

// Belirli bir düğümden sonra düğüm ekleme
void insertAfterNode(struct node *list, int data) {
    if (list == NULL) return;  // Eğer düğüm NULL ise, işlem yapılmaz

    // Yeni düğüm için bellek ayır
    struct node *lk = (struct node *)malloc(sizeof(struct node));
    lk->data = data;

    // Yeni düğümün next pointer'ını hedef düğümün next'ine bağla
    lk->next = list->next;

    // Hedef düğümün next pointer'ını yeni düğüme bağla
    list->next = lk;
}

// Başlangıçtaki düğümü silme
void deleteAtBegin() {
    if (head == NULL) return;  // Eğer liste boşsa, işlem yapılmaz

    struct node *temp = head;
    head = head->next;  // Baş düğümü bir sonraki düğüm yap
    free(temp);  // Silinen düğümün belleğini serbest bırak
}

// Son düğümü silme
void deleteAtEnd() {
    if (head == NULL) return;  // Eğer liste boşsa, işlem yapılmaz

    struct node *linkedlist = head;
    struct node *prev = NULL;

    // Son düğüme ulaşmak için listeyi tara
    while (linkedlist->next != NULL) {
        prev = linkedlist;
        linkedlist = linkedlist->next;
    }

    // Eğer sadece bir düğüm varsa
    if (prev == NULL) {
        head = NULL;
    } else {
        prev->next = NULL;  // Önceki düğümün next pointer'ını NULL yap
    }

    free(linkedlist);  // Silinen düğümün belleğini serbest bırak
}

// Belirli bir anahtara sahip düğümü silme
void deleteNode(int key) {
    struct node *temp = head, *prev = NULL;

    // İlk düğüm silinmek isteniyorsa
    if (temp != NULL && temp->data == key) {
        head = temp->next;  // Baş düğümü güncelle
        free(temp);  // Belleği serbest bırak
        return;
    }

    // Silinmek istenen düğümü bul
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Eğer düğüm bulunamazsa, işlem yapılmaz
    if (temp == NULL) return;

    // Düğümü listeden çıkar ve belleği serbest bırak
    prev->next = temp->next;
    free(temp);
}

// Listeyi arama fonksiyonu
int searchList(int key) {
    struct node *temp = head;

    // Listeyi tara ve anahtarı bulmaya çalış
    while (temp != NULL) {
        if (temp->data == key) {
            return 1;  // Eleman bulundu
        }
        temp = temp->next;
    }
    return 0;  // Eleman bulunamadı
}

// Tüm düğümleri serbest bırakma (bellek temizleme)
void freeList() {
    struct node *current = head;
    struct node *nextNode;

    // Listenin başından sonuna kadar tüm düğümleri tara ve serbest bırak
    while (current != NULL) {
        nextNode = current->next;
        free(current);  // Belleği serbest bırak
        current = nextNode;
    }

    head = NULL;  // Listenin başını sıfırla
}

int main() {
    int k = 0;

    insertAtBegin(12);
    insertAtBegin(22);
    insertAtEnd(30);
    insertAtEnd(44);
    insertAtBegin(50);
    insertAfterNode(head->next->next, 33);

    cout << "Linked List: ";
    printList();

    deleteAtBegin();
    deleteAtEnd();
    deleteNode(12);

    cout << "\nLinked List after deletion: ";
    printList();

    insertAtBegin(4);
    insertAtBegin(16);

    cout << "\nUpdated Linked List: ";
    printList();

    k = searchList(16);
    if (k == 1)
        cout << "\nElement is found";
    else
        cout << "\nElement is not present in the list";

    // Bellek sızıntılarını önlemek için tüm düğümleri serbest bırak
    freeList();

    cout << "\nLinked List after freeing memory: ";
    printList();

    return 0;
}
