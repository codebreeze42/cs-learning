#include <iostream>
#include <Stack>
#include <Queue>
using namespace std;
struct Vertex
{
    int vername;
    Edge *adjacent;
};
struct Edge
{
    int VerAdj;
    int weight;
    Edge *link;
};
// 深度优先算法
void DFS(Vertex Head[], int v, int visited[])
{
    visited[v] = 1;
    for (Edge *p = Head[v].adjacent; p != nullptr; p = p->link)
    {
        int k = p->VerAdj;
        if (visited[k] == 0)
            DFS(Head, k, visited);
    }
}
// 深度优先遍历的非递归算法
void DFS_Norec(Vertex Head[], int v, int n, int visited[])
{
    stack<int> S;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    S.push(v);
    while (!S.empty())
    {
        v = S.top();
        S.pop();
        if (visited[v] == 0)
        {
            visited[v] = 1;
            for (Edge *p = Head[v].adjacent; p != nullptr; p = p->link)
            {
                if (visited[p->VerAdj] == 0)
                    S.push(p->VerAdj);
            }
        }
    }
}
// 广度优先搜索
void BFS1(Vertex *Head[], int v, int n, int visited[])
{
    queue<int> Q;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[v] = 1;
    Q.push(v);
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        for (Edge *p = Head[v]->adjacent; p != nullptr; p = p->link)
        {
            if (visited[p->VerAdj] == 0)
            {
                visited[p->VerAdj] = 1; // 入队时访问
                Q.push(p->VerAdj);
            }
        }
    }
}
void BFS2(Vertex *Head[], int v, int n, int visited[])
{
    queue<int> Q;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[v] = 1;
    Q.push(v);
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        if (visited[v] == 1)
            continue;
        visited[v] = 1; // 出队时访问
        for (Edge *p = Head[v]->adjacent; p != nullptr; p = p->link)
        {
            if (visited[p->VerAdj] == 0)
                Q.push(p->VerAdj);
        }
    }
} // 效率更高
const int N = 100;
void BFS3(int n, int G[N][N], int v, int visited[])
{
    queue<int> Q;
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    visited[v] = 1;
    Q.push(v);
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        for (int w = 0; w < n; w++)
        {
            if (G[v][w] == 1 && visited[w] == 0)
            {
                visited[w] = 1;
                Q.push(w);
            }
        }
    }
}
// 图的应用
// 判断无向图是否连通及连通分量的数目
// 1.DFS
void conected1(int visited[])
{
    int n, cnt = 0;
    Vertex Head[10];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            DFS(Head, i, visited);
            cnt++;
        }
    }
}
// 2.并查集
int Parent[1000];
void Make_Set(int x)
{
    Parent[x] = 0;
}
int Find(int x)
{
    if (Parent[x] <= 0)
        return x;
    Parent[x] = Find(Parent[x]);
    return Parent[x];
}
void Union(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)
        return;
    if (Parent[fx] < Parent[fy])
        Parent[fy] = fx;
    else if (Parent[fx] > Parent[fy])
        Parent[fx] = fy;
    else
    {
        Parent[fx] = fy;
        Parent[fy]--;
    }
}
void conected2(int n, Vertex Head[])
{
    int count = 0;
    for (int i = 1; i <= n; i++)
        Make_Set(i);
    for (int i = 1; i <= n; i++)
    {
        int x = i;
        for (Edge *p = Head[i].adjacent; p != nullptr; p = p->link)
        {
            Union(x, p->VerAdj);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (Parent[i] <= 0)
            count++;
    }
}
// 判断图中顶点u到v是否存在路径
bool DFS_Path(Vertex Head[], int u, int v, int visited[])
{
    visited[u] = 1;
    if (u == v)
        return true;
    for (Edge *p = Head[u].adjacent; p != nullptr; p = p->link)
    {
        if (visited[p->VerAdj] == 0)

            if (DFS_Path(Head, p->VerAdj, v, visited))
                return true;
    }
    return false;
}
// 输出顶点u到v的所有路径
queue<int> path;
void DFS_AllPath(Vertex Head[], int u, int v, int visited[], queue<int> path)
{
    visited[u] = 1;
    path.push(u);
    if (u == v)
    {
        queue<int> temppath = path;
        while (!temppath.empty())
        {
            cout << temppath.front();
            temppath.pop();
        }
    }
    for (Edge *p = Head[u].adjacent; p != nullptr; p = p->link)
    {
        if (visited[p->VerAdj] == 0)
            DFS_AllPath(Head, p->VerAdj, v, visited, path);
    }
    path.pop();
    visited[u] = 0;
}
// 判断无向图是否有环
bool DFS_Cycle(Vertex *Head, int v, int visited[], int pre)
{
    visited[v] = 1;
    for (Edge *p = Head[v].adjacent; p != nullptr; p = p->link)
    {
        int k = p->VerAdj;
        if (visited[k] == 0)
        {
            if (DFS_Cycle(Head, k, visited, v))
                return true;
        }
        else if (k != pre)
            return true;
    }
    return false;
}

// 判断有向图是否有环
bool DFS_Cycle2(Vertex *Head, int v, int visited[])
{
    visited[v] = 1;
    for (Edge *p = Head[v].adjacent; p != nullptr; p = p->link)
    {
        int k = p->VerAdj;
        if (visited[k] == 0)
        {
            if (DFS_Cycle2(Head, k, visited))
                return true;
        }
        else if (visited[k] == 1)
            return true;
    }
    visited[v] = 2;
    return false;
}