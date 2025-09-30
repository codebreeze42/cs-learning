#include <iostream>
#include <stdio.h>
using namespace std;
long long D[200][200];
long long count[200][200] = {0};
const int INF = 0x3f3f3f3f;
void Floyd(int n, long long D[200][200], long long count[200][200])
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (k != i && k != j && i != j)
                {
                    if (D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        count[i][j] = count[i][k] * count[k][j];
                    }
                    else if (D[i][k] + D[k][j] == D[i][j])
                    {
                        count[i][j] += count[i][k] * count[k][j];
                    }
                }
            }
        }
    }
}
void calculate(int n, long long D[200][200], long long count[200][200])
{
    double result = 0;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (k != i && k != j && i != j && D[i][k] + D[k][j] == D[i][j])
                    result += 1.0 * D[i][j] * count[i][k] * count[k][j] / count[i][j];
            }
        }
        printf("%.3f\n", result);
        result = 0;
    }
}
int main()
{
    int n, e;
    cin >> n >> e;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                D[i][j] = 0;
                count[i][j] = 1;
            }
            else
                D[i][j] = INF;
        }
    }
    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        D[a][b] = c;
        D[b][a] = c;
        count[a][b] = 1;
        count[b][a] = 1;
    }
    Floyd(n, D, count);
    calculate(n, D, count);
}