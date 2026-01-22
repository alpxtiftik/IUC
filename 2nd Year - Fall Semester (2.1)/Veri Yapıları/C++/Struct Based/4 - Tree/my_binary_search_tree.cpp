#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Root node oluşturma
struct node* createRoot(int key) {
    struct node* root = new node();
    root->data = key;
    root->left = root->right = NULL;
    return root;
}

// Ağaca yeni eleman ekleme (Binary Search Tree insert)
struct node* insert(struct node* root, int key) {
    if (root == NULL) {
        root = createRoot(key);  // Eğer kök yoksa yeni bir kök oluştur
    } else {
        if (key < root->data) {  // Sol alt ağaca ekleme
            root->left = insert(root->left, key);
        } else if (key > root->data) {  // Sağ alt ağaca ekleme
            root->right = insert(root->right, key);
        }
        // Aynı değeri tekrar eklememek için else bloğu eklenebilir.
    }
    return root;
}

// Pre-order traversal (Kök -> Sol -> Sağ)
void preOrder(struct node* root) {
    if (root != NULL) {
        cout << root->data << ", ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// In-order traversal (Sol -> Kök -> Sağ)
void inOrder(struct node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << ", ";
        inOrder(root->right);
    }
}

// Post-order traversal (Sol -> Sağ -> Kök)
void postOrder(struct node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << ", ";
    }
}

// Ağacın toplam düğüm sayısını hesaplama
int cntNode(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return cntNode(root->left) + 1 + cntNode(root->right);
    }
}

// Ağacın yüksekliğini hesaplama
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int left = height(root->left);
        int right = height(root->right);
        return max(left, right) + 1;
    }
}

// Sol ve sağ dalların yer değiştirmesi
void chngPlace(struct node* root) {
    if (root != NULL) {
        chngPlace(root->left);
        chngPlace(root->right);

        // Sol ve sağ alt ağaçların yer değiştirilmesi
        struct node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

// Belleği temizlemek için ağacı silme fonksiyonu
void destroyTree(struct node* root) {
    if (root != NULL) {
        destroyTree(root->left);  // Sol alt ağacı sil
        destroyTree(root->right); // Sağ alt ağacı sil
        delete root;              // Kendi düğümünü sil
    }
}

int main() {
    struct node* root = NULL;
    int sayi;

    // Kullanıcıdan 7 sayı alıp ağaca ekleme
    for (int i = 0; i < 7; i++) {
        cout << "Sayi girin: ";
        cin >> sayi;
        root = insert(root, sayi);
    }

    // Traversal sonuçları
    cout << endl << "preOrder: ";
    preOrder(root);
    cout << endl;

    cout << "inOrder: ";
    inOrder(root);
    cout << endl;

    cout << "postOrder: ";
    postOrder(root);
    cout << endl;

    // Düğüm sayısı ve yüksekliği
    cout << endl << "Eklenen node sayisi: " << cntNode(root) << endl;
    cout << "Tree Height: " << height(root) << endl;

    // Dalların yer değiştirmesi
    chngPlace(root);
    cout << endl << "Dallar yer degistirdi. " << endl;

    // Yer değiştirme sonrası traversal
    cout << "preOrder: ";
    preOrder(root);
    cout << endl;

    cout << "inOrder: ";
    inOrder(root);
    cout << endl;

    cout << "postOrder: ";
    postOrder(root);
    cout << endl;

    // Belleği temizleme
    destroyTree(root);
    cout << "Bellek temizlendi." << endl;

    return 0;
}
