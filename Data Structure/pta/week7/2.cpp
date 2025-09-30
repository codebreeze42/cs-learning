#include <iostream>
using namespace std;
int graph[200][200] = {0};
int R[200][200];
int scc[200];
void Warshall(int graph[200][200], int n, int R[200][200])
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            R[i][j] = graph[i][j];
        }
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
            }
        }
    }
}
int SCC(int graph[200][200], int n, int scc[])
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            R[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        scc[i] = 0;
    }
    Warshall(graph, n, R);
    int num = 0;
    for (int i = 1; i <= n; i++)
    {
        if (scc[i] == 0)
        {
            scc[i] = ++num;
            for (int j = 1; j <= n; j++)
            {
                if (scc[j] == 0 && R[i][j] == 1 && R[j][i] == 1)
                {
                    scc[j] = num;
                }
            }
        }
    }
    return num;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int temp = n;
        int count = 1;
        while (n--)
        {
            int t;
            cin >> t;
            while (t != 0)
            {
                graph[count][t] = 1;
                cin >> t;
            }
            count++;
        }
        int num = SCC(graph, temp, scc);
        cout << num << endl;
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 200; j++)
            {
                graph[i][j] = 0;
            }
        }
    }
    return 0;
}