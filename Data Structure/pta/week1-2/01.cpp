#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool isMatched(string s)
{
    stack<char> bracket;
    int n = s.size();
    char pair[150] = {0};
    char order[150] = {0};
    pair['('] = ')';
    pair['['] = ']';
    pair['{'] = '}';
    pair['<'] = '>';
    order['('] = 2;
    order['['] = 3;
    order['{'] = 4;
    order['<'] = 1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<')
        {
            if (bracket.empty())
                bracket.push(s[i]);
            else
            {
                if (order[s[i]] < order[bracket.top()])
                    bracket.push(s[i]);
                else
                    return false;
            }
        }

        else if (s[i] == ')' || s[i] == ']' || s[i] == '}' || s[i] == '>')
        {
            if (bracket.empty())
                return false;
            char t = bracket.top();
            if (pair[t] != s[i])
                return false;
            else
                bracket.pop();
        }
    }
    return bracket.empty();
}

int main()
{
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> s;
        if (isMatched(s))
            cout << "Match" << endl;
        else
            cout << "Fail" << endl;
    }
    cin >> s;
    if (isMatched(s))
        cout << "Match";
    else
        cout << "Fail";
    return 0;
}