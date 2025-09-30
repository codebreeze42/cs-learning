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
void cal_depth(int pre[], int n)
{
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
}
int maxPath(int pre[], int a, int b)
{
    int maxpath1 = 0, maxpath2 = 0, maxpath;
    int a1 = a;
    int b1 = b;
    while (depth[a1] > depth[b])
    {
        a1 = pre[a1];
    }
    while (depth[a] < depth[b1])
    {
        b1 = pre[b1];
    }
    while (a1 != b1)
    {
        a1 = pre[a1];
        b1 = pre[b1];
    }
    while (a != a1)
    {
        maxpath1 = max(maxpath1, G[a][pre[a]]);
        a = pre[a];
    }
    while (b != b1)
    {
        maxpath2 = max(maxpath2, G[b][pre[b]]);
        b = pre[b];
    }
    maxpath = max(maxpath1, maxpath2);
    return maxpath;
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
// void OutputMST(int Lowcost[], int pre[], int n)
// {                                // 输出MST中的边
//     for (int v = 1; v <= n; v++) // 输出MST中的边 (pre[v],v)及权值
//         if (pre[v] != -1)
//             printf("edge : % d - % d, weight : % d\n", pre[v], v, Lowcost[v]);
// }
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
    // OutputMST(Lowcost, pre, n);
    cal_depth(pre, n);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << maxPath(pre, a, b) << endl;
    }
    return 0;
}