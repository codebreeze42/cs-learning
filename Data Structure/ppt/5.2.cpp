// 进制转换
#include <string>
#include <stack>
#include <cmath>
using namespace std;
string convertToBase7(int n)
{
    if (n == 0)
        return "0";
    stack<int> s;
    string ans = (n > 0) ? "" : "-";
    n = abs(n);
    while (n > 0)
    {
        s.push(n % 7);
        n /= 7;
    }
    while (!s.empty())
    {
        ans += s.top() + '0';
        s.pop();
    }
    return ans;
}