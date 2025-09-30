#include <iostream>
#include <cmath>
using namespace std;
struct ListNode{
    int data;
    ListNode* next;
    ListNode(int x){
        data=x;
        next=nullptr;
    }
};

void remove_equal(ListNode*head,int m){
    if(head->next==nullptr) return;
    bool*seen=new bool[m]();
    ListNode* current=head->next;
    ListNode* prev=head;
    while(current!=nullptr){
        int absv=abs(current->data);
        if(seen[absv]){
            prev->next=current->next;
            delete current;
        }
        else{
            seen[absv]=true;
            prev=current;
        }
        current=prev->next;
    }
    delete []seen;
}