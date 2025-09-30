#include <iostream>
#include <string>
using namespace std;
void buildnext(string p, int next[], int m)
{
    next[0] = -1;
    int k = -1;
    for (int j = 0; j < m - 1; j++)
    {
        while (p[k] != p[j] && k >= 0)
        {
            k = next[k];
        }
        next[j + 1] = k + 1;
        next[m] = (m / 5 - 1) * 5;
    }
}

int KMP(string s, string p)
{
    int n = s.size();
    int m = p.size();
    int next[100000] = {0};
    int i = 0, j = 0;
    int count = 0;
    buildnext(p, next, m);
    while (j < m && i < n)
    {
        if (s[i] == p[j] || j == -1)
        {
            i++;
            j++;
        }
        else
            j = next[j];
        if (j == m)
        {
            count++;
            j = next[j];
        }
    }
    return count;
}

int main()
{
    int n, m;
    cin >> n;
    string s, p;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        cin >> m;
        p = "";
        for (int t = 0; t < m; t++)
        {
            p = p + "edgnb";
        }
        cout << KMP(s, p) << endl;
    }
    return 0;
}