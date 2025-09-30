#include <iostream>
#include <stack>
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
void getInDegree(Vertex *Head[], int n, int InDegree[])
{
    for (int i = 0; i < n; i++)
    {
        InDegree[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (Edge *p = Head[i]->adjcent; p != nullptr; p = p->link)
            InDegree[p->Veradj]++;
    }
}

void TopoOrder(Vertex *Head[], int n)
{
    const int N = n;
    int InDegree[N];
    getInDegree(Head, n, InDegree);
    for (int i = 0; i < n; i++)
    {
        int signal = -1;
        for (int i = 0; i < n; i++)
        {
            if (InDegree[i] == 0)
            {
                signal = i;
                cout << i << ' ';
                InDegree[i] = -1;
                for (Edge *p = Head[i]->adjcent; p != nullptr; p = p->link)
                {
                    InDegree[p->Veradj]--;
                }
                break;
            }
        }
        if (signal == -1)
        {
            cout << "unworkable project";
            break;
        }
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
    for (int i = 0; i < e; i++)
    {
        int Vername, Veradj;
        cin >> Vername >> Veradj;
        Initialize(Head, Vername, Veradj);
    }
    TopoOrder(Head, n);
    return 0;
}