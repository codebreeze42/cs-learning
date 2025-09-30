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
    Edge *adjacent;
};

void Initialize(Vertex *Head[], int Vername, int Veradj, int cost)
{
    Head[Vername]->Vername = Vername;
    Edge *current = new Edge();
    current->link = nullptr;
    current->Veradj = Veradj;
    current->cost = cost;
    if (!Head[Vername]->adjacent)
    {
        Head[Vername]->adjacent = current;
    }
    else
    {
        Edge *p = Head[Vername]->adjacent;
        Edge *pre = nullptr;

        while (p != nullptr && Veradj > p->Veradj)
        {
            pre = p;
            p = p->link;
        }
        if (pre == nullptr)
        {
            current->link = Head[Vername]->adjacent;
            Head[Vername]->adjacent = current;
        }
        else
        {
            pre->link = current;
            current->link = p;
        }
    }
}
int main()
{
    int n, e;
    int Vername, Veradj, cost;
    cin >> n >> e;
    const int max_n = n;
    Vertex *Head[max_n];
    for (int i = 0; i < n; i++)
    {
        Head[i] = new Vertex();
        Head[i]->adjacent = nullptr;
    }
    for (int i = 0; i < e; i++)
    {
        cin >> Vername >> Veradj >> cost;
        Initialize(Head, Vername, Veradj, cost);
    }
    for (int i = 0; i < n; i++)
    {
        if (Head[i]->adjacent != nullptr)
        {
            cout << i << ':';
            for (Edge *p = Head[i]->adjacent; p != nullptr; p = p->link)
            {
                int Vername = Head[i]->Vername;
                int Veradj = p->Veradj;
                int cost = p->cost;
                cout << '(' << Vername << ',' << Veradj << ',' << cost << ')';
            }
            cout << endl;
        }
    }
    return 0;
}