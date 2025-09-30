// 栈混洗的甄别
#include <stack>
using namespace std;
bool check(int a[], int b[], int n)
{
    stack<int> s;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        while (s.empty() || s.top() != b[i])
        {
            if (k < n)
                s.push(a[k++]);
            else
                return false;
        }
        s.pop();
    }
    return true;
}