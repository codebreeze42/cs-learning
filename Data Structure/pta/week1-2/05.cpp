#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void buildNext(string p, int next[], int m)
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

int calculate(string p)
{
    int next[100010];
    int m = p.size();
    buildNext(p, next, m);
    int result = next[m];
    result = next[result];
    int Q = max(m - 2 * max(result, 0), 0);
    reverse(p.begin(), p.end());
    string temp = p;
    int next2[100010];
    buildNext(p, next2, m);
    int P = *max_element(next2, next2 + m + 1);
    return P + Q;
}

int main()
{
    string p;
    while (getline(cin, p))
    {
        if (p.empty())
            continue;
        else
            cout << calculate(p) << endl;
    }
    return 0;
}