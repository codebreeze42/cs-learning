#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
int G[2020][2020];
int G2[2020][2020];
int pre[2020] = {-1};
int Lowcost[2020] = {INF};
int depth[2020] = {0};
int FindMin(int S[], int Lowcost[], int n)
{
    int v = -1, min = INF;
    for (int i = 1; i <= n; i++)
    {
        if (S[i] == 0 && Lowcost[i] < min)
        {
            min = Lowcost[i];
            v = i;
        }
    }
    return v;
}
void maxPath(int pre[], int n)
{
    for (int j = 2; j <= n; j++)
    {
        int i = j;
        while (pre[pre[i]] != -1)
        {
            G2[j][pre[pre[i]]] = (G2[j][pre[i]] > G[pre[pre[i]]][pre[i]] ? G2[j][pre[i]] : G[pre[pre[i]]][pre[i]]);
            G2[pre[pre[i]]][j] = G2[j][pre[pre[i]]];
            i = pre[i];
        }
    }
    depth[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        int j = i;
        while (pre[j] != -1)
        {
            depth[i]++;
            j = pre[j];
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            if (i != j)
            {
                int d1 = depth[i];
                int d2 = depth[j];
                if (d1 == d2)
                {
                    int temp = d1;
                    int i1 = i, j1 = j;
                    while (pre[i1] != pre[j1])
                    {
                        i1 = pre[i1];
                        j1 = pre[j1];
                    }
                    int w = pre[i1];
                    G2[i][j] = max(G2[i][w], G2[j][w]);
                    G2[j][j] = G2[i][j];
                }
                else
                {
                }
            }
        }
    }
}
void Prim1(int G[2020][2020], int n, int u, int Lowcost[], int pre[])
{
    int S[2020] = {0};
    for (int i = 1; i <= n; i++)
    {
        pre[i] = -1;
        Lowcost[i] = (i == u) ? 0 : INF;
    }
    for (int i = 1; i <= n; i++)
    {
        int v = FindMin(S, Lowcost, n);
        if (v == -1)
            return;
        S[v] = 1;
        for (int w = 1; w <= n; w++)
        {
            if (S[w] == 0 && G[v][w] < Lowcost[w])
            {
                Lowcost[w] = G[v][w];
                pre[w] = v;
            }
        }
    }
}
void OutputMST(int Lowcost[], int pre[], int n)
{                                // 输出MST中的边
    for (int v = 1; v <= n; v++) // 输出MST中的边 (pre[v],v)及权值
        if (pre[v] != -1)
            printf("edge : % d - % d, weight : % d\n", pre[v], v, Lowcost[v]);
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                G[i][j] = 0;
                G2[i][j] = 0;
            }
            else
            {
                G[i][j] = INF;
                G2[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        G[a][b] = c;
        G[b][a] = c;
        G2[a][b] = c;
        G2[b][a] = c;
    }
    Prim1(G, n, 1, Lowcost, pre);
    OutputMST(Lowcost, pre, n);
    maxPath(pre, n);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << G2[a][b] << endl;
    }
    return 0;
}