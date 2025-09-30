#include <iostream>
using namespace std;
bool check(int x)
{
    int p = 1;
    while (x > 0)
    {
        if (x % 10 % 2 == p % 2)
        {
            p++;
            x /= 10;
        }
        else
            return false;
    }
    return true;
}
int main()
{
    int n, res = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        if (check(i))
            res++;
    }
    cout << res;
    return 0;
}