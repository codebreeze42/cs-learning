// 括号匹配
#include <string>
#include <stack>
using namespace std;
bool isValid(string s)
{
    int n = s.size();
    stack<char> bracket;
    char pair[150] = {0};
    pair['('] = ')';
    pair['['] = ']';
    pair['{'] = '}';
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            bracket.push(s[i]);
        else
        {
            if (bracket.empty())
                return false;
            if (pair[bracket.top()] == s[i])
                bracket.pop();
            else
                return false;
        }
    }
    return bracket.empty();
}