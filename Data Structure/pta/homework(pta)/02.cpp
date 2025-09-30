#include <iostream>
#include <cassert>
using namespace std;
class Stack
{
public:
    bool full() { return top == size - 1; }
    bool empty() { return top == -1; }
    void push(int d)
    {
        assert(!full());
        A[++top] = d;
    }
    int pop()
    {
        assert(!empty());
        return A[top--];
    }

private:
    int A[20000];
    int top = -1;
    int size = 20000;
};

int main()
{
    Stack stack;
    int n, op, d;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> d;
            stack.push(d);
        }
        else if (op == 0)
        {
            if (stack.empty())
            {
                cout << "invalid" << endl;
            }
            else
            {
                cout << stack.pop() << endl;
            }
        }
    }
    return 0;
}