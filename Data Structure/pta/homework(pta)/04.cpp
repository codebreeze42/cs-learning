#include <iostream>
#include <string>
using namespace std;
void buildnext(string p, int next[], int m)
{
    next[0] = -1;
    int k = -1;
    for (int j = 0; j < m - 1; j++)
    {
        while (k >= 0 && p[k] != p[j])
        {
            k = next[k];
        }
        next[j + 1] = ++k;
    }
}
int KMP(string s, string p, int n, int m)
{
    int next[100000];
    int i = 0, j = 0;
    buildnext(p, next, m);
    while (j < m && i < n)
    {
        if (s[i] == p[j])
        {
            i++;
            j++;
        }
        else if (j == 0)
            i++;
        else
            j = next[j];
    }
    return (j == m) ? i - m : -1;
}

int main()
{
    string s, p;
    int n, m;
    int next[100000];
    getline(cin, s);
    getline(cin, p);
    n = s.length();
    m = p.length();
    buildnext(p, next, m);
    cout << next[m / 4] << " " << next[2 * m / 4] << " " << next[3 * m / 4] << " " << endl;
    cout << KMP(s, p, n, m);
    return 0;
}