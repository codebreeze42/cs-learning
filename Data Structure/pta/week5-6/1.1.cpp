#include <iostream>
using namespace std;
const int max_v = 20010;
int Matrix[max_v][max_v] = {0};
void InitialMat(int Matrix[][max_v], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            Matrix[i][j] = 0;
    }
}
void add(int Matrix[][max_v], int vername, int veradj, int cost)
{
    Matrix[vername][veradj] = cost;
}
int main()
{
    int n, e;
    cin >> n >> e;
    for (int i = 0; i < e; i++)
    {
        int vername, veradj, cost;
        cin >> vername >> veradj >> cost;
        add(Matrix, vername, veradj, cost);
    }
    for (int i = 0; i < n; i++)
    {

        bool isPath = false;
        for (int j = 0; j < n; j++)
        {
            if (Matrix[i][j] != 0)
            {
                if (!isPath)
                {
                    cout << i << ':';
                    isPath = true;
                }
                cout << '(' << i << ',' << j << ',' << Matrix[i][j] << ')';
            }
        }
        if (isPath)
            cout << endl;
    }
    return 0;
}