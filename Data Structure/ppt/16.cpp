#include <iostream>
#include <Stack>
using namespace std;
const int N = 100;
struct Vertex
{
    int vername;
    Edge *adjacent;
};
struct Edge
{
    int VerAdj;
    Edge *link;
};
void getInDegree(Vertex Head[], int n, int InDegree[])
{
    for (int i = 0; i < n; i++)
    {
        InDegree[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (Edge *p = Head[i].adjacent; p != nullptr; p = p->link)
        {
            InDegree[p->VerAdj]++;
        }
    }
}
bool TopoOrder(Vertex Head[], int n)
{
    int InDegree[N];
    stack<int> s;
    getInDegree(Head, n, InDegree);
    for (int i = 0; i < n; i++)
    {
        if (InDegree[i] == 0)
            s.push(i);
    }
    for (int i = 0; i < n; i++)
    {
        if (s.empty())
            return false;
        int j = s.top();
        s.pop();
        for (Edge *p = Head[j].adjacent; p != nullptr; p = p->link)
        {
            InDegree[p->VerAdj]--;
            if (InDegree[p->VerAdj] == 0)
                s.push(p->VerAdj);
        }
    }
    return true;
}

// 深度优先搜索生成逆拓扑序
void DFS_TopoSort(Vertex *Head, int v, int visited[])
{
    visited[v] = 1;
    for (Edge *p = Head[v].adjacent; p != nullptr; p = p->link)
    {
        if (visited[p->VerAdj] == 0)
            DFS_TopoSort(Head, p->VerAdj, visited);
    }
    printf("%d", v);
}
void DFS(Vertex *Head, int n, int visited[])
{
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
            DFS_TopoSort(Head, i, visited);
    }
}