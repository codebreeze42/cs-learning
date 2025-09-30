#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
struct Edge
{
    int VerAdj;
    int cost;
    Edge *link;
};
struct vertex
{
    int verName;
    Edge *adjacent;
};
vertex graph[20020];
void initVertex(int n)
{
    for (int i = 1; i <= n; i++)
    {
        graph[i].verName = i;
        graph[i].adjacent = nullptr;
    }
}
void initEdge_train(int a, int b, int c)
{
    Edge *cur = new Edge;
    cur->cost = c;
    cur->VerAdj = b;
    cur->link = graph[a].adjacent;
    graph[a].adjacent = cur;
    Edge *cur2 = new Edge;
    cur2->cost = c;
    cur2->VerAdj = a;
    cur2->link = graph[b].adjacent;
    graph[b].adjacent = cur2;
}
int findmin(int S[], int dist[], int n)
{
    int v = -1, min = INF;
    for (int i = 1; i <= n; i++)
    {
        if (S[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            v = i;
        }
    }
    return v;
}
int Dijkstra(vertex graph[], int n, int s, int t, int dist[])
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
    }
    int S[20020] = {0};
    dist[s] = 0;
    for (int i = 1; i <= n; i++)
    {
        int v = findmin(S, dist, n);
        if (v == -1)
            return INF;
        S[v] = 1;
        for (Edge *p = graph[v].adjacent; p != nullptr; p = p->link)
        {
            int w = p->VerAdj;
            if (S[w] == 0 && dist[v] + p->cost < dist[w])
            {
                dist[w] = dist[v] + p->cost;
            }
        }
    }
    return dist[t];
}
int main()
{
    int n, s, t;
    while (cin >> n >> s >> t)
    {
        int dist1[20020] = {INF};
        int dist2[20020] = {INF};
        initVertex(n);
        int m;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            initEdge_train(a, b, c);
        }
        int distance = Dijkstra(graph, n, s, t, dist1);
        int temp = Dijkstra(graph, n, t, s, dist2);
        int k;
        cin >> k;
        int rail_num = 0;
        for (int i = 0; i < k; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            if (dist1[x] + z + dist2[y] < distance)
            {
                distance = dist1[x] + z + dist2[y];
                rail_num = x;
            }
            else if (dist1[y] + z + dist2[x] < distance)
            {
                distance = dist1[y] + z + dist2[x];
                rail_num = y;
            }
        }
        cout << distance << endl;
        if (rail_num != 0)
            cout << rail_num << endl;
        else
            cout << "no metro" << endl;
    }
    return 0;
}