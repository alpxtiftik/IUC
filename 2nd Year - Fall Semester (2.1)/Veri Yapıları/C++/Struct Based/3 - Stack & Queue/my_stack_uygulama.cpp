//ISG Kurs Kayıt Uygulaması 

#include <iostream>
using namespace std;
#define SIZE 10

//Stack yapısı ve elemanlar (Node) ayrıldı, okunabilirlik katıyor. 
struct node {
    int id; 
    string name; 
    string surname; 
    string department; 
    struct node * next;

};

struct stack {
    struct node * top = NULL; //En üst değeri tutuyor. 
    int cnt = 0;
};

bool isFull(stack * stc){   
    return(stc->cnt == SIZE);
}

bool isEmpty(stack * stc){
    return(stc->cnt == 0);
}

void add(stack * stc, int id, string name, string surname, string department){
    struct node * ogr = new node();
    ogr->id = id;
    ogr->name = name; 
    ogr->surname = surname;
    ogr->department = department;

    if (isFull(stc)){
        cout << "Stack is Full." << endl;
    }
    else if (isEmpty(stc)){
        stc->top = ogr;
        stc->top->next = NULL;
        stc->cnt ++;
        cout << id << "numarali ogrenci kursa kayit edildi" << endl;
    }
    else {
        ogr->next = stc->top;
        stc->top = ogr; 
        stc->cnt ++;  
        cout << id << "numarali ogrenci kursa kayit edildi" << endl;
    }
}

void delet(stack * stc){
    if (isEmpty(stc)) {
        cout << "Kursta kayitli ogrenci yok" << endl;
    }
    else if(stc->top->next = NULL){//1 düğüm varsa. 
        cout << stc->top->id << "numaralı öğrenci silindi" << endl;
        delete stc->top; 
        stc->cnt--;
    }
    else {
        struct node * temp = stc->top->next; 
        cout << stc->top->id << "numaralı öğrenci silindi" << endl;
        delete stc->top;
        stc->top = temp;  
    }
}

void print(stack *stc){
    if (isEmpty(stc)){
        cout<<"kayitli ogrenci yok"<<endl;
    }
    else{
        struct node * iter = stc->top;
        while (iter->next!=NULL){
            cout << iter->id << iter->name << iter->surname << endl;
            iter = iter ->next;
        }
        cout << iter->id << iter->name << iter->surname << endl;
    }
    
}




int main(){

}
