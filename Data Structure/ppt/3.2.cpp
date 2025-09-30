//双链表
#include <iostream>;
using namespace std;
    struct ListNode{
        ListNode* next;
        ListNode* prev;
        int data;
        ListNode(int n){data=n;prev=next=nullptr;}
    };

class Linkedlist{
private:
ListNode* head;
public:
Linkedlist(){
    head=new ListNode(0);
}

void DeleteNode(ListNode* head,ListNode*s){
    if(s==nullptr||s==head) return;
    ListNode* prev=s->prev;
    ListNode* next=s->next;
    prev->next=next;
    next->prev=prev;
    delete s;
}

void InsertNode(ListNode* head,ListNode* p,int k){ //在指针p指向的结点右侧插入结点
    if(p==nullptr) return;
    ListNode* s=new ListNode(k);
    ListNode* next=p->next;
    next->prev=s;
    s->next=next;
    s->prev=p;
    p->next=s;
}
};    