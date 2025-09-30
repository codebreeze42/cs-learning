struct ListNode{
    int data;
    int freq;
    ListNode* prev;
    ListNode* next;
};

class LinkedNode{
private:
ListNode* head;
public:
LinkedNode(){
    head=new ListNode();
    head->prev=head;
    head->next=head;
    head->data=0;
    head->freq=0;
    }
ListNode* visit(ListNode*head,int K){
    ListNode* p=head->next;
    ListNode* q=head->next;
    while(p!=head&&p->data!=K){
        p=p->next;
    }
    if(p==head) return nullptr;
    else p->freq=p->freq+1;
        
    while(q->freq>p->freq){
        q=q->next;
    }
    p->prev->next=p->next;
    p->next->prev=p->prev;
    ListNode* Prev=q->prev;
    p->next=q;
    p->prev=Prev;
    Prev->next=p;
    q->prev=p;    
    return p;
}
   
};