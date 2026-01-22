#include <iostream>
#include <cstdlib>  // malloc ve free fonksiyonları için gerekli

// AVL Ağacı Düğümü Yapısı
struct Node {
   int data;
   struct Node *leftChild;
   struct Node *rightChild;
   int height;  // Düğümün yüksekliği
};

// Yardımcı fonksiyonlar
int max(int a, int b);

// Düğümün yüksekliğini döndürür
int height(struct Node *N) {
   if (N == NULL)
      return 0;
   return N->height;
}

// İki değerden büyük olanı döndürür
int max(int a, int b) {
   return (a > b) ? a : b;
}

// Yeni düğüm oluşturma fonksiyonu
struct Node *newNode(int data) {
   struct Node *node = (struct Node *) malloc(sizeof(struct Node));
   if (node == NULL) {
       std::cerr << "Memory allocation failed!\n";
       exit(EXIT_FAILURE);  // Bellek tahsisi başarısızsa program sonlandırılır
   }
   node->data = data;
   node->leftChild = NULL;
   node->rightChild = NULL;
   node->height = 1;  // Yeni düğüm başlangıçta yaprak düğümdür (yükseklik 1)
   return node;
}

// Sağ rotasyon fonksiyonu
struct Node *rightRotate(struct Node *y) {
   struct Node *x = y->leftChild;
   struct Node *T2 = x->rightChild;

   // Döndürme işlemi
   x->rightChild = y;
   y->leftChild = T2;

   // Yükseklikleri güncelle
   y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
   x->height = max(height(x->leftChild), height(x->rightChild)) + 1;

   return x;  // Yeni kök döndürülür
}

// Sol rotasyon fonksiyonu
struct Node *leftRotate(struct Node *x) {
   struct Node *y = x->rightChild;
   struct Node *T2 = y->leftChild;

   // Döndürme işlemi
   y->leftChild = x;
   x->rightChild = T2;

   // Yükseklikleri güncelle
   x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
   y->height = max(height(y->leftChild), height(y->rightChild)) + 1;

   return y;  // Yeni kök döndürülür
}

// Düğümün denge faktörünü hesaplar
int getBalance(struct Node *N) {
   if (N == NULL)
      return 0;
   return height(N->leftChild) - height(N->rightChild);
}

// Yeni düğüm ekleme (AVL ağacına)
struct Node *insertNode(struct Node *node, int data) {
   // 1. Normal BST ekleme işlemi
   if (node == NULL)
      return newNode(data);

   if (data < node->data)
      node->leftChild = insertNode(node->leftChild, data);
   else if (data > node->data)
      node->rightChild = insertNode(node->rightChild, data);
   else  // Aynı veri eklenmeye çalışılıyorsa, ekleme yapılmaz
      return node;

   // 2. Düğüm yüksekliğini güncelle
   node->height = 1 + max(height(node->leftChild), height(node->rightChild));

   // 3. Denge faktörünü hesapla
   int balance = getBalance(node);

   // 4. Ağacı dengelemek için dört olası durum
   if (balance > 1 && data < node->leftChild->data)  // Sol-Sol durumu
      return rightRotate(node);

   if (balance < -1 && data > node->rightChild->data)  // Sağ-Sağ durumu
      return leftRotate(node);

   if (balance > 1 && data > node->leftChild->data) {  // Sol-Sağ durumu
      node->leftChild = leftRotate(node->leftChild);
      return rightRotate(node);
   }

   if (balance < -1 && data < node->rightChild->data) {  // Sağ-Sol durumu
      node->rightChild = rightRotate(node->rightChild);
      return leftRotate(node);
   }

   return node;  // Değişiklik yapılmadıysa aynı düğüm döndürülür
}

// Minimum değeri bulan fonksiyon (silme işleminde kullanılır)
struct Node *minValueNode(struct Node *node) {
   struct Node *current = node;

   // En soldaki yaprak düğümü bulur
   while (current->leftChild != NULL)
      current = current->leftChild;

   return current;
}

// Düğüm silme fonksiyonu
struct Node *deleteNode(struct Node *root, int data) {
   // 1. Normal BST silme işlemi
   if (root == NULL)
      return root;

   if (data < root->data)
      root->leftChild = deleteNode(root->leftChild, data);
   else if (data > root->data)
      root->rightChild = deleteNode(root->rightChild, data);
   else {
      // Tek çocuklu veya çocuksuz düğüm durumu
      if ((root->leftChild == NULL) || (root->rightChild == NULL)) {
         struct Node *temp = root->leftChild ? root->leftChild : root->rightChild;

         // Çocuksuz düğüm
         if (temp == NULL) {
            temp = root;
            root = NULL;
         } else  // Tek çocuklu düğüm
            *root = *temp;  // Düğümün içeriğini kopyala

         free(temp);  // Geçici düğümü serbest bırak
      } else {
         // İki çocuklu düğüm
         struct Node *temp = minValueNode(root->rightChild);

         // Sağdaki en küçük değeri köke kopyala
         root->data = temp->data;

         // En küçük değeri sağ alt ağaçtan sil
         root->rightChild = deleteNode(root->rightChild, temp->data);
      }
   }

   if (root == NULL)
      return root;

   // 2. Yükseklik güncellemesi
   root->height = 1 + max(height(root->leftChild), height(root->rightChild));

   // 3. Denge faktörünü kontrol et
   int balance = getBalance(root);

   // Dört olası dengeleme durumu
   if (balance > 1 && getBalance(root->leftChild) >= 0)
      return rightRotate(root);

   if (balance > 1 && getBalance(root->leftChild) < 0) {
      root->leftChild = leftRotate(root->leftChild);
      return rightRotate(root);
   }

   if (balance < -1 && getBalance(root->rightChild) <= 0)
      return leftRotate(root);

   if (balance < -1 && getBalance(root->rightChild) > 0) {
      root->rightChild = rightRotate(root->rightChild);
      return leftRotate(root);
   }

   return root;
}

// Ağacı in-order olarak yazdırma (Küçükten büyüğe sıralı)
void printTree(struct Node *root) {
   if (root != NULL) {
      printTree(root->leftChild);
      printf("%d ", root->data);
      printTree(root->rightChild);
   }
}

int main() {
   struct Node *root = NULL;

   // AVL Ağacına düğümler ekle
   root = insertNode(root, 22);
   root = insertNode(root, 14);
   root = insertNode(root, 72);
   root = insertNode(root, 44);
   root = insertNode(root, 25);
   root = insertNode(root, 63);
   root = insertNode(root, 98);

   printf("AVL Tree: ");
   printTree(root);  // Ağacı yazdır

   // Düğüm silme işlemi
   root = deleteNode(root, 25);
   printf("\nAfter deletion: ");
   printTree(root);  // Ağacı tekrar yazdır

   return 0;
}
