#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool Operation(stack<int> &num, stack<char> &op, int &result)
{
    int y = num.top();
    num.pop();
    int x = num.top();
    num.pop();
    char t = op.top();
    op.pop();
    switch (t)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
        if (y == 0)
        {

            return false;
        }
        result = x / y;
        break;
    case '^':
        result = 1;

        while (y > 0)
        {
            if (y % 2 == 1)
                result = result * x;
            x = x * x;
            y = y / 2;
        }
        break;
    }
    return true;
}

int readNum(string s, int n, int &i)
{
    int num = 0;
    while (s[i] >= '0' && s[i] <= '9' && i < n)
    {
        num = num * 10 + s[i] - '0';
        i++;
    }
    i--;
    return num;
}
bool Calculate(string p, int &finalResult)
{
    int n = p.size();
    stack<int> num;
    stack<char> op;
    int q[100] = {0};
    int result = 0;
    q['+'] = q['-'] = 1;
    q['*'] = q['/'] = 2;
    q['^'] = 3;
    for (int i = 0; i < n; i++)
    {
        if (p[i] >= '0' && p[i] <= '9')
            num.push(readNum(p, n, i));
        else if (p[i] == '(')
            op.push(p[i]);
        else if (p[i] == ')')
        {

            while (op.top() != '(')
            {

                if (!Operation(num, op, result))
                    return false;
                num.push(result);
            }
            op.pop();
        }
        else
        {
            while (!op.empty() && op.top() != '(' && q[(int)p[i]] <= q[(int)op.top()])
            {

                if (!Operation(num, op, result))
                    return false;
                num.push(result);
            }
            op.push(p[i]);
        }
    }
    while (!op.empty())
    {

        if (!Operation(num, op, result))
            return false;
        num.push(result);
    }
    finalResult = num.top();
    return true;
}

int main()
{
    string p;
    int finalResult;
    bool isFirstLine = true;
    while (getline(cin, p))
    {
        if (p.empty())
            continue;
        if (!isFirstLine)
            cout << endl;
        isFirstLine = false;
        if (Calculate(p, finalResult))
            cout << finalResult;
        else
            cout << "INVALID";
    }
    return 0;
}