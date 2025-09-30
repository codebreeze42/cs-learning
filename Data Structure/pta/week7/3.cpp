#include <iostream>
#include <stdio.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int dist[200][200];
long long count[200][200] = {0};
void Floyd(int n, int dist[200][200])
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    count[i][j] = count[i][k] * count[k][j];
                    // cout<<i<<k<<j<<endl;
                    // cout<<"count["<<i<<"]["<<j<<"]"<<":"<<count[i][k]<<"*"<<count[k][j]<<endl;
                }
                else if (dist[i][k] + dist[k][j] == dist[i][j] && i != j && i != k && k != j)
                {
                    // long long temp=count[i][j];
                    count[i][j] += count[i][k] * count[k][j];
                    // cout<<i<<k<<j<<endl;
                    // cout<<"count["<<i<<"]["<<j<<"]"<<":"<<temp<<"+"<<count[i][k]<<"*"<<count[k][j]<<endl;
                }
            }
        }
    }
}
void cal(int dist[200][200], int n, long long count[200][200])
{
    double result = 0;
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != k && j != i && j != k && dist[i][k] + dist[k][j] == dist[i][j])
                { // cout<<i<<j<<k;
                    // double temp=result;
                    result += 1.0 * dist[i][j] * count[i][k] * count[k][j] / count[i][j];
                    // cout<<temp + 1.0 * dist[i][j] * count[i][k] * count[k][j] / count[i][j]<<" ";
                }
            }
        }
        if (result)
        {
            printf("%.3f\n", result);
            result = 0;
        }
        else
            printf("0.000\n");
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
                dist[i][j] = 0;
                count[i][j] = 1;
            }
            else
                dist[i][j] = INF;
        }
    }
    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
        dist[b][a] = c;
        count[a][b] = 1;
        count[b][a] = 1;
    }
    Floyd(n, dist);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         cout << dist[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cal(dist, n, count);
    return 0;
}