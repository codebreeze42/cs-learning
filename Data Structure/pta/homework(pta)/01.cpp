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
    };
};

class Linkedlist
{
private:
    ListNode *head;
    int size;

public:
    Linkedlist(int d)
    {
        head = new ListNode(d);
        size = 1;
    }
    void add(int k)
    {
        ListNode *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new ListNode(k);
        size++;
    }

    void insert(int k, int d)
    {
        ListNode *temp = head;
        if (k == 0)
        {
            ListNode *temp2 = new ListNode(d);
            temp2->next = head;
            head = temp2;
            size++;
        }
        else if (k > 0 && k <= size)
        {
            for (int i = 0; i < k - 1; i++)
            {
                temp = temp->next;
            }
            ListNode *temp2 = new ListNode(d);

            temp2->next = temp->next;
            temp->next = temp2;
            size++;
        }
    }

    void Delete(int k)
    {
        ListNode *prev = head;
        if (k == 1)
        {
            head = head->next;
            delete prev;
            size--;
        }
        else if (k > 1 && k <= size)
        {
            for (int i = 0; i < k - 2; i++)
            {
                prev = prev->next;
            }
            ListNode *current = prev->next;
            ListNode *next = current->next;
            prev->next = next;
            delete current;
            size--;
        }
    }

    void show()
    {
        ListNode *temp = head;
        while (temp)
        {
            cout << temp->data;
            cout << " ";
            temp = temp->next;
        }
    }
};

int main()
{
    int n, data, m, op, k, d;
    cin >> n;
    cin >> data;
    Linkedlist linkedlist(data);
    for (int i = 1; i < n; i++)
    {
        cin >> data;
        linkedlist.add(data);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        cin >> k;
        if (op == 0)
        {
            cin >> d;
            linkedlist.insert(k, d);
        }
        else if (op == 1)
        {
            linkedlist.Delete(k);
        }
    }
    linkedlist.show();
    return 0;
}