// 栈的数组实现
#include <cassert>
const int maxsize = 1e4 + 10;
template <class T>
class Stack
{
public:
    bool full() { return top == maxsize - 1; }
    bool empty() { return top == -1; }
    void push(T K)
    {
        assert(!full())
            A[++top] = K;
    }
    T pop()
    {
        assert(!empty());
        return A[top--];
    }
    T peek()
    {
        assert(!empty());
        return A[top];
    }

private:
    int top = -1;
    T A[maxsize];
};