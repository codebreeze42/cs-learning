#include <iostream>
#include <stack>
using namespace std;
struct Edge
{
    int head;
    int tail;
    int weight;
};
Edge E[300000];
int parent[1000];
void swap(Edge &a, Edge &b)
{
    int temp_head = a.head;
    int temp_tail = a.tail;
    int temp_weight = a.weight;
    a.head = b.head;
    a.tail = b.tail;
    a.weight = b.weight;
    b.head = temp_head;
    b.tail = temp_tail;
    b.weight = temp_weight;
}
int Partition(Edge E[], int m, int n)
{
    int K = E[m].weight, L = m + 1, G = n;
    while (L <= G)
    {
        while (L <= n && E[L].weight <= K)
            L++;
        while (E[G].weight > K)
            G--;
        if (L < G)
        {
            swap(E[L], E[G]);
            L++;
            G--;
        }
    }
    swap(E[m], E[G]);
    return G;
}
void QuickSort(Edge E[], int m, int n)
{
    stack<int> s;
    s.push(m);
    s.push(n);
    while (!s.empty())
    {
        n = s.top();
        s.pop();
        m = s.top();
        s.pop();
        if (m < n)
        {
            int k = Partition(E, m, n);
            // if (m < k - 1)
            // {
            s.push(m);
            s.push(k - 1);
            // }
            // if (k + 1 < n)
            // {
            s.push(k + 1);
            s.push(n);
            // }
        }
    }
}
void Make_Set(int x)
{
    parent[x] = 0;
}
int Find(int x)
{
    if (parent[x] <= 0)
        return x;
    parent[x] = Find(parent[x]);
    return parent[x];
}
void Union(int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)
        return;
    if (parent[fx] < parent[fy])
        parent[fy] = fx;
    else if (parent[fy] < parent[fx])
        parent[fx] = fy;
    else
    {
        parent[fx] = fy;
        parent[fy]--;
    }
}
int Kruskal(Edge E[], int n, int e)
{
    for (int i = 0; i < n; i++)
        Make_Set(i);
    QuickSort(E, 0, e - 1);
    int sum = 0, k = 0;
    for (int i = 0; i < e; i++)
    {
        int u = E[i].head, v = E[i].tail, w = E[i].weight;
        if (Find(u) != Find(v))
        {
            k++;
            sum += w;
            Union(u, v);
        }
        if (k == n - 1)
            return sum;
    }
    return -1;
}
int main()
{
    int n, e;
    // cin >> n >> e;
    scanf("%d %d", &n, &e);
    for (int i = 0; i < n; i++)
    {
        E[i].head = i;
        E[i].tail = n;
        scanf("%d", &E[i].weight);
        // cin >> E[i].weight;
    }
    for (int i = 0; i < e; i++)
    {
        scanf("%d", &E[i + n].head);
        scanf("%d", &E[i + n].tail);
        scanf("%d", &E[i + n].weight);
    }
    int num = Kruskal(E, n + 1, n + e);
    cout << num << endl;
    return 0;
}