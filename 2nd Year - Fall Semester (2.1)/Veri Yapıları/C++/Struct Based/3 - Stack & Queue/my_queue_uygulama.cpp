#include <iostream>
using namespace std; 

#define SIZE 10 
#define UCRET 3

struct node {
    string ad; 
    int adet, ucret; 
    struct node * next; 
};

struct queue {
    int cnt; 
    struct node * front;
    struct node * rear; 
};

void initialize(queue * q){
    q->cnt = 0; 
    q->rear = q->front = NULL; 
}

bool isFull(queue * q){
    return(q->cnt == SIZE);
}

bool isEmpty(queue * q){
    return(q->cnt == 0);
}

void enqueue(queue * q, string ad, int adet){
    struct node * add = new node; 
    add->ad = ad; 
    add->adet = adet;
    add->ucret = (adet * UCRET);
    if(isFull(q)){//Dolu 
        cout << "Pide kuyrugu dolu." << endl; 
    }
    else if(isEmpty(q)){//Boş
        cout << "Pide kuyrugu bostu, ilk siraya biri eklendi" << endl;
        q->front = q->rear = add; 
        add->next = NULL;
        q->cnt++;
    }
    else{//En az 1 eleman.
        q->rear->next = add; 
        q->rear = add; 
        add->next = NULL;
        q->cnt++;
    }
}