// 中缀转后缀求值
#include <stack>
#include <string>
using namespace std;
int readnum(string s, int n, int &i)
{
    int temp = 0;
    while (i < n && s[i] >= '0' && s[i] <= '9')
    {
        temp = temp * 10 + s[i] - '0';
        i++;
    }
    i--;
    return temp;
}

void operation(stack<int> &num, stack<char> &op)
{
    char t = op.top();
    op.pop();
    int a = num.top();
    num.pop();
    int b = num.top();
    num.pop();
    if (t == '+')
        num.push(a + b);
    else if (t == '-')
        num.push(a - b);
    else if (t == '*')
        num.push(a * b);
    else
        num.push(a / b);
}

int calculate(string s)
{
    stack<int> num;
    stack<char> op;
    int n = s.size();
    int p[100] = {0};
    p['+'] = p['-'] = 1;
    p['*'] = p['/'] = 2;
    for (int i = 1; i < n; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num.push(readnum(s, n, i));
        else if (s[i] == '(')
            op.push(s[i]);
        else if (s[i] = ')')
        {
            while (op.top() != '(')
            {
                operation(num, op);
            }
            op.pop();
        }
        else
        {
            while (!op.empty() && op.top() != '(' && p[s[i]] <= p[op.top()])
            {
                operation(num, op);
            }
            op.push(s[i]);
        }
    }
    while (!op.empty())
        operation(num, op);
    return num.top();
}