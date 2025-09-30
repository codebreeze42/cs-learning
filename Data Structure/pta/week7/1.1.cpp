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
                if (w == t)
                    break;
            }
        }
    }
    return dist[t];
}
void Dijkstra_rail(vertex graph[], int n, int s, int t, int dist[], int &rail_num, int &distance)
{
    int x, y, z;
    cin >> x >> y >> z;
    Edge *cur_edge = graph[x].adjacent;
    int temp = INF;
    while (cur_edge != nullptr)
    {
        if (cur_edge->VerAdj == y)
        {
            temp = cur_edge->cost;
            if (z >= cur_edge->cost)
            {
                distance = dist[t];
                rail_num = 0;
                return;
            }
            cur_edge->cost = z;
            break;
        }
        cur_edge = cur_edge->link;
    }
    if (temp == INF)
    {
        cur_edge = new Edge;
        cur_edge->cost = z;
        cur_edge->VerAdj = y;
        cur_edge->link = graph[x].adjacent;
        graph[x].adjacent = cur_edge;
    }
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
            break;
        S[v] = 1;
        for (Edge *p = graph[v].adjacent; p != nullptr; p = p->link)
        {
            int w = p->VerAdj;
            // cout << w << S[w] << dist[v] << p->cost << dist[w] << endl;
            if (S[w] == 0 && dist[v] + p->cost < dist[w])
            {
                dist[w] = dist[v] + p->cost;
                // cout << w << dist[w] << endl;
                if (w == t)
                    break;
            }
        }
    }
    if (dist[t] < distance)
    {
        distance = dist[t];
        rail_num = x;
        // cout << "YES" << endl;
    }
    else if (dist[t] == distance)
    {
        if (x < rail_num)
            rail_num = x;
        // cout << "YES1" << endl;
    }
    if (temp != INF)
        cur_edge->cost = temp;
    else
    {
        graph[x].adjacent = cur_edge->link;
        delete cur_edge;
    }
}
int main()
{
    int n, s, t;
    while (cin >> n >> s >> t)
    {
        int dist[20020] = {INF};
        initVertex(n);
        int m;
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            initEdge_train(a, b, c);
        }
        int distance = Dijkstra(graph, n, s, t, dist);
        int k;
        cin >> k;
        int rail_num = 0;
        for (int i = 0; i < k; i++)
        {
            Dijkstra_rail(graph, n, s, t, dist, rail_num, distance);
        }
        cout << distance << endl;
        if (rail_num != 0)
            cout << rail_num << endl;
        else
            cout << "no metro" << endl;
    }
    return 0;
}