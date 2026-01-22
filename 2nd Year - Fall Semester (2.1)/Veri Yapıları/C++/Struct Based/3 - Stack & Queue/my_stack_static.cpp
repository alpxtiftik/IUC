//STACK STATIC UYGULAMA

#include <iostream>
using namespace std; 

#define SIZE 10

struct stack {
    int data[SIZE]; 
    int top = -1; //Index değerini tutuyor. 
};

stack stc;

void push (int key){ //Stack'e ekleme yapar. 
    if(stc.top == SIZE - 1) {
        cout << "Stack dolu." << endl; 
    }
    else {
        stc.top++;
        stc.data[stc.top]=key;
        cout << "Stack'e veri girişi yapıldı." << endl;
    }

}

void pop(){ //Stack'den veri çıkarır.
    if (stc.top == -1){
        cout << "Stack boş." << endl;
    }
    else {
        stc.top--;
        cout << stc.data[stc.top] << "değeri, stack'ten çıkarıldı." << endl;
    }
}

void reset(){ //Stack'i boşaltır.
    stc.top = -1;
    cout << "Stack resetlendi." << endl;
}

void print(){ //Stack'teki verileri yazdırır. 
    for (int i = stc.top; i>-1; i--){
        cout << stc.data[i] << endl; 
    }
}

int main(){




    return 0; 
}