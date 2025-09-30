#include <iostream>
using namespace std;
struct Edge
{
    int Veradj;
    Edge *link;
    int cost;
};
struct Vertex
{
    int Vername;
    Edge *adjcent;
};
const int INF = 0x3f3f3f3f, maxn = 20010;
void Initialize(Vertex *Head[], int Vername, int Veradj, int cost)
{
    Head[Vername]->Vername = Vername;
    if (!Head[Vername]->adjcent)
    {
        Head[Vername]->adjcent = new Edge();
        Head[Vername]->adjcent->Veradj = Veradj;
        Head[Vername]->adjcent->cost = cost;
        Head[Vername]->adjcent->link = nullptr;
        return;
    }
    Edge *p = Head[Vername]->adjcent;
    Edge *current = new Edge();
    current->link = nullptr;
    while (p->link)
    {
        p = p->link;
    }
    p->link = current;
    current->Veradj = Veradj;
    current->cost = cost;
}
int findMin(int S[], int dist[], int n)
{
    int v = -1, min = INF;
    for (int i = 0; i < n; i++)
    {
        if (S[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            v = i;
        }
    }
    return v;
}
void Dijkstra(Vertex *Head[], int n, int u, int dist[])
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
    }
    int S[maxn] = {0};
    dist[u] = 0;
    for (int i = 0; i < n; i++)
    {
        int v = findMin(S, dist, n);
        if (v == -1)
        {
            for (int i = 1; i < n; i++)
            {
                if (dist[i] != INF)
                    cout << dist[i] << ' ';
            }
            return;
        }
        S[v] = 1;
        for (Edge *p = Head[v]->adjcent; p != nullptr; p = p->link)
        {
            int w = p->Veradj;
            if (S[w] == 0 && dist[v] + p->cost < dist[w])
            {
                dist[w] = dist[v] + p->cost;
            }
        }
    }
}
int main()
{
    int n, e;
    cin >> n >> e;
    Vertex *Head[maxn];
    int dist[maxn];
    for (int i = 0; i < n; i++)
    {
        Head[i] = new Vertex();
        Head[i]->adjcent = nullptr;
    }
    for (int i = 0; i < e; i++)
    {
        int Vername, Veradj, cost;
        cin >> Vername >> Veradj >> cost;
        Initialize(Head, Vername, Veradj, cost);
    }
    int u = 0;
    Dijkstra(Head, n, u, dist);
    return 0;
}
