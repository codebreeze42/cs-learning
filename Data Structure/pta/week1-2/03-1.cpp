#include <iostream>
#include <string>
#include <stack>
#include <cmath> // For using pow function
using namespace std;

int Operation(int x, char t, int y)
{
    int result = 0;
    if (t == '+')
        result = x + y;
    else if (t == '-')
        result = x - y;
    else if (t == '*')
        result = x * y;
    else if (t == '/')
    {
        if (y == 0)
        {
            cout << "INVALID" << endl;
            exit(1); // Exit since division by zero is undefined
        }
        result = x / y;
    }
    else if (t == '^')
    {
        result = 1;
        for (int i = 0; i < y; i++)
        {
            result *= x;
        }
    }
    return result;
}

int readNum(string s, int n, int &i)
{
    int num = 0;
    while (i < n && s[i] >= '0' && s[i] <= '9')
    {
        num = num * 10 + s[i] - '0';
        i++;
    }
    i--;
    return num;
}

int Calculate(string p)
{
    int n = p.size();
    stack<int> num;
    stack<char> op;
    int q[256] = {0};
    q['+'] = q['-'] = 1;
    q['*'] = q['/'] = 2;
    q['^'] = 3;

    for (int i = 0; i < n; i++)
    {
        if (p[i] >= '0' && p[i] <= '9')
        {
            num.push(readNum(p, n, i));
        }
        else if (p[i] == '(')
        {
            op.push(p[i]);
        }
        else if (p[i] == ')')
        {
            while (!op.empty() && op.top() != '(')
            {
                char temp = op.top();
                op.pop();
                int y = num.top();
                num.pop();
                int x = num.top();
                num.pop();
                num.push(Operation(x, temp, y));
            }
            op.pop();
        }
        else
        {
            while (!op.empty() && op.top() != '(' && q[op.top()] >= q[p[i]])
            {
                char temp = op.top();
                op.pop();
                int y = num.top();
                num.pop();
                int x = num.top();
                num.pop();
                num.push(Operation(x, temp, y));
            }
            op.push(p[i]);
        }
    }

    while (!op.empty())
    {
        char temp = op.top();
        op.pop();
        int y = num.top();
        num.pop();
        int x = num.top();
        num.pop();
        num.push(Operation(x, temp, y));
    }

    return num.top();
}

int main()
{
    string expression;
    cout << "Enter the expression: ";
    cin >> expression;
    cout << "Result: " << Calculate(expression) << endl;
    return 0;
}