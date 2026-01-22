#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Yeni düğüm oluşturma
struct node* createNode(int key) {
    struct node* newNode = new node();
    newNode->data = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Ağaca düğüm ekleme (Binary Tree için rastgele ekleme)
struct node* insert(struct node* root, int key, bool toLeft) {
    if (root == NULL) {  // Kök düğüm yoksa oluştur
        return createNode(key);
    }
    
    // Eğer ağacın soluna eklemek istiyorsak
    if (toLeft) {
        if (root->left == NULL) {
            root->left = createNode(key);
        } else {
            insert(root->left, key, toLeft);  // Sol dal doluysa ilerle
        }
    }
    // Sağ tarafa eklemek istiyorsak
    else {
        if (root->right == NULL) {
            root->right = createNode(key);
        } else {
            insert(root->right, key, toLeft);  // Sağ dal doluysa ilerle
        }
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

// Düğüm sayısını hesaplama
int cntNode(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + cntNode(root->left) + cntNode(root->right);
}

// Ağacın yüksekliğini hesaplama
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    int left = height(root->left);
    int right = height(root->right);
    return max(left, right) + 1;
}

// Sol ve sağ alt ağaçları yer değiştirme
void chngPlace(struct node* root) {
    if (root != NULL) {
        chngPlace(root->left);
        chngPlace(root->right);

        // Sol ve sağ dalları değiştir
        struct node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

// Ağacı serbest bırakma (Belleği temizleme)
void destroyTree(struct node* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

// Ana fonksiyon
int main() {
    struct node* root = NULL;
    int sayi;
    bool toLeft;

    // Kullanıcıdan 7 sayı alıp ağaca ekleme (Binary Tree rastgele dallar)
    for (int i = 0; i < 7; i++) {
        cout << "Sayi girin: ";
        cin >> sayi;
        cout << "Bu sayiyi sol dalda mi ekleyelim? (1: Evet, 0: Hayir): ";
        cin >> toLeft;

        root = insert(root, sayi, toLeft);
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
    cout << endl << "Dallar yer degistirdi." << endl;

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

    // Ağacı serbest bırakma (Bellek temizleme)
    destroyTree(root);
    cout << "Bellek temizlendi." << endl;

    return 0;
}
