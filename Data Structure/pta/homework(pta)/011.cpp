#include <iostream>
using namespace std;

struct ListNode
{
    int data;
    ListNode *next;
    ListNode(int d) : data(d), next(nullptr) {}
};

class Linkedlist
{
private:
    ListNode *head;

public:
    Linkedlist() { head = nullptr; } // 空链表初始化

    // 添加到链表末尾
    void add(int k)
    {
        if (head == nullptr)
        { // 如果链表为空，直接创建头节点
            head = new ListNode(k);
        }
        else
        {
            ListNode *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = new ListNode(k);
        }
    }

    // 在第 k 个位置插入节点 d，k 从 0 开始计数
    void insert(int k, int d)
    {
        if (k == 0)
        { // 在链表头插入
            ListNode *newNode = new ListNode(d);
            newNode->next = head;
            head = newNode;
        }
        else
        {
            ListNode *temp = head;
            for (int i = 0; i < k - 1 && temp; ++i)
            {
                temp = temp->next;
            }
            if (temp)
            { // 确保找到位置
                ListNode *newNode = new ListNode(d);
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    // 删除第 k 个节点，k 从 1 开始计数
    void Delete(int k)
    {
        if (head == nullptr)
            return; // 如果链表为空，直接返回

        if (k == 1)
        { // 删除头节点的特殊情况
            ListNode *toDelete = head;
            head = head->next;
            delete toDelete;
        }
        else
        {
            ListNode *prev = head;
            for (int i = 1; i < k - 1 && prev; ++i)
            {
                prev = prev->next;
            }
            if (prev && prev->next)
            {
                ListNode *toDelete = prev->next;
                prev->next = toDelete->next;
                delete toDelete;
            }
        }
    }

    // 显示链表内容
    void show()
    {
        ListNode *temp = head;
        while (temp)
        {
            cout << temp->data;
            if (temp->next)
            {
                cout << " ";
            }
            temp = temp->next;
        }
        cout << endl; // 输出后换行
    }
};

int main()
{
    int n, data, m, op, k, d;
    cin >> n; // 当前链表的长度

    Linkedlist linkedlist; // 初始化空链表

    // 添加链表中的节点
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        linkedlist.add(data); // 添加节点
    }

    cin >> m; // 操作数
    for (int i = 0; i < m; i++)
    {
        cin >> op >> k;
        if (op == 0)
        { // 插入操作
            cin >> d;
            if (0 <= k && k <= n)
            { // 插入位置合法

                linkedlist.insert(k, d);
                n++; // 插入后长度增加
            }
        }
        else if (op == 1)
        { // 删除操作
            if (1 <= k && k <= n)
            { // 删除位置合法
                linkedlist.Delete(k);
                n--; // 删除后长度减少
            }
        }
    }

    // 显示链表的最终内容
    linkedlist.show();
    return 0;
}
