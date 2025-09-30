#include <iostream>
#include <cassert>
using namespace std;
class Queue
{
public:
    bool empty()
    {
        return front == rear;
    }
    bool full()
    {
        return (rear + 1) % size == front;
    }
    void enQueue(int d)
    {
        assert(!full());
        A[rear] = d;
        rear = (rear + 1) % size;
    }
    int deQueue()
    {
        assert(!empty());
        int d = A[front];
        front = (front + 1) % size;
        return d;
    }

private:
    int A[20000];
    int size = 20000;
    int front = 0;
    int rear = 0;
};

int main()
{
    Queue queue;
    int n, op, d;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> d;
            queue.enQueue(d);
        }
        else if (op == 0)
        {
            if (queue.empty())
            {
                cout << "invalid" << endl;
            }
            else
            {
                cout << queue.deQueue() << endl;
            }
        }
    }
    return 0;
}