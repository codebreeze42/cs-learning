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

long long shortest(string p, long long m, long long next[])
{
    long long result = m;

    if (next[m] == 0)
        return 0;

    while (next[result])
    {
        result = next[result];
    }
    result = m - result;
    return result;
}

int main()
{
    long long m;
    string p;
    cin >> m;
    cin >> p;
    long long *next = new long long[m + 1];
    buildNext(p, next, m);
    int finalResult = shortest(p, m, next);
    m = m - 1;
    for (; m > 0; m--)
    {

        finalResult += shortest(p, m, next);
    }
    cout << finalResult << endl;
    delete[] next;
    return 0;
}