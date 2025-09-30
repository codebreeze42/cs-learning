// 链表的创建及相关操作
#include <iostream>
using namespace std;

struct ListNode
{
    int data;
    ListNode *next;
    ListNode(int d)
    {
        data = d;
        next = nullptr;
    }
};

class Linkedlist
{
private:
    ListNode *head;

public:
    Linkedlist()
    {
        head = new ListNode(0);
    }

    ListNode *headInsert(int len)
    {
        ListNode *p = head;
        int k;
        while (len--)
        {
            scanf("%d", &k);
            insertRight(head, p, k);
        }
        return head;
    }

    void insertRight(ListNode *head, ListNode *p, int val)
    { // 尾插法
        if (p == nullptr)
            return;
        ListNode *s = new ListNode(val);
        s->next = p->next;
        p->next = s;
    }

    ListNode *OrderedSearch(ListNode *head, int k)
    {
        if (k < 0)
            return nullptr;
        int i = 0;
        ListNode *p = head;
        while (p && i < k)
        {
            p = p->next;
            i++;
        }
        return p;
    }

    ListNode *ValueSearch(ListNode *head, int v)
    {
        ListNode *p = head->next;
        while (p && p->data != v)
        {
            p = p->next;
        }
        return p;
    }

    ListNode *FindPrev(ListNode *head, ListNode *p)
    {
        if (p == nullptr)
            return nullptr;
        for (ListNode *q = head; q != nullptr; q = q->next)
        {
            if (q->next == p)
                return q;
        }
        return nullptr;
    }

    int Length(ListNode *head)
    {
        ListNode *p = head->next;
        int l = 0;
        while (p)
        {
            l++;
            p = p->next;
        }
        return l;
    }

    void deleteNode(ListNode *head, int k)
    { // 删除第k个结点
        if (k < 1 || k > Length(head))
        {
            cout << "输入有误" << endl;
            return;
        }
        ListNode *prev = OrderedSearch(head, k - 1);
        ListNode *target = OrderedSearch(head, k);
        prev->next = target->next;
        delete target;
    }

    void deleteNodePlus(ListNode *p)
    { // 删除p指向的结点升级版,更小的时间复杂度
        if (p->next != nullptr)
        {
            ListNode *q = p->next;
            p->data = q->data;
            p->next = q->next;
            delete q;
        }
    }

    void deleteNodeRight(ListNode *head, ListNode *p)
    { // 删除p的后继结点
        if (p == nullptr || p->next == nullptr)
            return;
        ListNode *q = p->next;
        p->next = q->next;
        delete q;
    }
};
