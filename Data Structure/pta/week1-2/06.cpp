#include <iostream>
#include <string>
using namespace std;
void buildNext(string p, long long next[], long long m)
{
    int k = -1;
    next[0] = -1;
    for (int j = 0; j <= m - 1; j++)
    {
        while (k >= 0 && p[k] != p[j])
            k = next[k];
        next[j + 1] = ++k;
    }
}

int main()
{
    long long m;
    string p;
    cin >> m;
    cin >> p;
    long long *next = new long long[m + 1];
    buildNext(p, next, m);
    long long finalResult = 1;

    for (int i = 2, j = 2; i <= m; i++, j = i)
    {
        while (next[j])
            j = next[j];
        if (next[i])
            next[i] = j;
        finalResult += i - j;
    }
    cout << finalResult << endl;
    delete[] next;
    return 0;
}