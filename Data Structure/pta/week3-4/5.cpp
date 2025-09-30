#include <iostream>
using namespace std;
int Parent[1010];
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
    else if (Parent[fy] < Parent[fx])
        Parent[fx] = fy;
    else
    {
        Parent[fx] = fy;
        Parent[fy]--;
    }
}
void isEqual(int n, int m, int q)
{
    int x, y;
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        Make_Set(i);
    }
    while (m--)
    {
        cin >> x >> y;
        Union(x, y);
    }
    while (q--)
    {
        cin >> x >> y;
        if (Find(x) == Find(y))
            cout << "In the same gang." << endl;
        else
            cout << "In different gangs." << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        if (Parent[i] <= 0)
            count++;
    }
    cout << count << endl;
}
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    isEqual(n, m, q);
    return 0;
}