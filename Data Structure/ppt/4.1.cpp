#include <iostream>
#include<cmath>
using namespace std;
struct ListNode{
    int data;
    ListNode* next;
    ListNode(int n){data=n;next=nullptr;}
};

class Linkedlist{
private:
ListNode* head;
public:
Linkedlist(){
    head=new ListNode(0);
}
// 给定一个不含哨位结点的单链表，请设计一个尽可能高效的算法，查找链表中倒数第k个结点（k为正整数）。若查找成功，算法返回该结点的数据域之值；否则返回0。
int kth_to_last(ListNode*head,int k){
    ListNode*slow=head,*fast=head;
    for(int i=1;fast!=nullptr&&i<k;i++)
    fast=fast->next;
    if(fast==nullptr) return 0;
    while(fast->next!=nullptr){
        fast=fast->next;
        slow=slow->next;
    }
    return slow->data;
}

//找单链表中间位置的结点，要求只遍历一次链表。若链表长度为偶数，返回两个中间结点中靠右的那个结点。

ListNode* midNode(ListNode* head){
    ListNode*fast=head,*slow=head;
    if(fast!=nullptr&&fast->next!=nullptr){
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}

//反转单链表
ListNode* reverseList(ListNode* head){
    if(head==nullptr) return head;
    ListNode*p=head,*q=head->next;
    while(q!=nullptr){
        p->next=q->next;
        q->next=head;
        head=q;
        q=p->next;
    }
    return head;
}

//找交点
ListNode* cross(ListNode* head1,ListNode* head2){
    if(head1==nullptr||head2==nullptr) return nullptr;
    if(head1==head2) return head1;
    ListNode* p1=head1,*p2=head2;
    int L1=1,L2=1;
    while(p1->next!=nullptr){L1++;p1=p1->next;}
    while(p2->next!=nullptr){L2++;p2=p2->next;}
    if(p1!=p2) return nullptr;
    if(L1<L2) {p1=head2;p2=head1;}
    else{p1=head1;p2=head2;}
    for(int i=0;i<abs(L1-L2);i++) p1=p1->next;
    while(p1!=p2) {p1=p1->next;p2=p2->next;}
    return p1;
}

//判断是否成环
bool hasCycle(ListNode *head) {
        ListNode*slow=head,*fast=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast) return true;
        }
        return false;
    }

//寻找环的起点
ListNode* detectCycleEntrance(ListNode *head){
    ListNode*slow=head,*fast=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
                ListNode*p1=head,*p2=slow;
                while(p1!=p2){
                    p1=p1->next;
                    p2=p2->next;
                }
                return p1;
            }
}  
return nullptr;
} 
};

