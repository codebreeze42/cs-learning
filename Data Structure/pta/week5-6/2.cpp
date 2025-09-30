#include <iostream>
using namespace std;
struct Edge
{
    int Veradj;
    Edge *link;
};
struct Vertex
{
    int Vername;
    Edge *adjcent;
};
void Initialize(Vertex *Head[], int Vername, int Veradj)
{
    Head[Vername]->Vername = Vername;
    if (!Head[Vername]->adjcent)
    {
        Head[Vername]->adjcent = new Edge();
        Head[Vername]->adjcent->Veradj = Veradj;
        Head[Vername]->adjcent->link = nullptr;
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
}
void sort(Edge *p)
{
    if (p == nullptr || p->link == nullptr)
        return;
    Edge *curr = p;
    while (curr != nullptr)
    {
        Edge *min = curr;
        Edge *temp = curr->link;
        while (temp != nullptr)
        {
            if (temp->Veradj < min->Veradj)
            {
                min = temp;
            }
            temp = temp->link;
        }
        if (min != curr)
        {
            int temp_Veradj = curr->Veradj;
            curr->Veradj = min->Veradj;
            min->Veradj = temp_Veradj;
        }
        curr = curr->link;
    }
}
void DFS(Vertex *Head[], int v, int visited[])
{
    cout << v << ' ';
    visited[v] = 1;
    for (Edge *p = Head[v]->adjcent; p != nullptr; p = p->link)
    {
        int k = p->Veradj;
        if (visited[k] == 0)
            DFS(Head, k, visited);
    }
}
int main()
{
    int n, e;
    cin >> n >> e;
    const int max_n = n;
    Vertex *Head[max_n];
    for (int i = 0; i < n; i++)
    {
        Head[i] = new Vertex();
        Head[i]->adjcent = nullptr;
    }
    int visited[max_n] = {0};
    for (int i = 0; i < e; i++)
    {
        int Vername, Veradj;
        cin >> Vername >> Veradj;
        Initialize(Head, Vername, Veradj);
    }
    for (int i = 0; i < n; i++)
    {
        sort(Head[i]->adjcent);
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
            DFS(Head, i, visited);
    }
    return 0;
}