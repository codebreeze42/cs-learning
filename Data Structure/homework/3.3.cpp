#include <iostream>
using namespace std;

#define MAXSIZE 100

class TwoStacks{
private:
int arr[MAXSIZE];
int top1;
int top2;

public:
TwoStacks(){
    top1=-1;
    top2=MAXSIZE;
}

void push1(int x){
    if(top1<top2-1) arr[++top1]=x;
    else cout<<"栈S1已满"<<endl;
}

void push2(int x){
    if(top1<top2-1) arr[--top2]=x;
    else cout<<"栈S2已满"<<endl;
}

int pop1(){
    if(top1>=0) return arr[top1--];
    else {
        cout<<"栈已空"<<endl;
        return 0;
    }
}

int pop2(){
    if(top2<MAXSIZE) return arr[top2++];
    else {
        cout<<"栈已空"<<endl;
        return 0;
    }
}

bool isEmpty1(){
    return top1==-1;
}

bool isEmpty2(){
    return top2==MAXSIZE;
}

bool isFull(){
    return top1==top2-1;
}

};