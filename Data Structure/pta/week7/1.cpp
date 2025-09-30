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
vertex graph[22000];
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
    int S[22000] = {0};
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
void Dijkstra_rail(vertex graph[], int n, int s, int t, int dist[], int &rail_num, int &distance)
{
    int x, y, z;
    int rail_num2 = INF;
    cin >> x >> y >> z;
    Edge *cur_edge = graph[x].adjacent;
    int temp = INF;
    while (cur_edge != nullptr)
    {
        if (cur_edge->VerAdj == y)
        {
            temp = cur_edge->cost;
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
    Edge *cur_edge2 = graph[y].adjacent;
    int temp2 = INF;
    while (cur_edge2 != nullptr)
    {
        if (cur_edge2->VerAdj == x)
        {
            temp2 = cur_edge2->cost;
            cur_edge2->cost = z;
            break;
        }
        cur_edge2 = cur_edge2->link;
    }
    if (temp == INF)
    {
        cur_edge2 = new Edge;
        cur_edge2->cost = z;
        cur_edge2->VerAdj = x;
        cur_edge2->link = graph[y].adjacent;
        graph[y].adjacent = cur_edge2;
    }
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
    }
    int S[22000] = {0};
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
            if (S[w] == 0 && dist[v] + p->cost < dist[w])
            {
                dist[w] = dist[v] + p->cost;
                if (v == x || v == y)
                {
                    rail_num2 = (v == x) ? y : x;
                }
            }
        }
    }
    if (dist[t] < distance)
    {
        distance = dist[t];
        rail_num = rail_num2;
    }
    else if (dist[t] == distance)
    {
        if (rail_num2 < rail_num)
        {
            rail_num = rail_num2;
            // cout<<rail_num2<<" "<<rail_num<<endl;
        }
    }
    if (temp != INF)
        cur_edge->cost = temp;
    else
    {
        graph[x].adjacent = cur_edge->link;
        delete cur_edge;
    }
    if (temp2 != INF)
        cur_edge2->cost = temp2;
    else
    {
        graph[y].adjacent = cur_edge2->link;
        delete cur_edge2;
    }
}
int main()
{
    int n, s, t;
    while (cin >> n >> s >> t)
    {
        int dist[22000] = {INF};
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