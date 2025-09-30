#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f, maxn = 110;
int x, y, tx, ty, n, m;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; // 与上下左右顺序无关
int dist[maxn][maxn], map[maxn][maxn];
void Initialize(int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a;
            cin >> a;
            if (a == 3)
            {
                x = i;
                y = j;
                map[i][j] = a;
            }
            else if (a == 4)
            {
                tx = i;
                ty = j;
                map[i][j] = 0;
            }
            else
            {
                map[i][j] = a;
            }
        }
    }
}
bool feasible(int x, int y)
{
    if (x >= 0 && x < n && y >= 0 && y < m && map[x][y] == 0 && dist[x][y] == INF)
        return true;
    return false;
}
void DFS(int n, int m, int x, int y, int tx, int ty, int map[][maxn], int dist[][maxn])
{
    queue<int> Q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dist[i][j] = INF;
        }
    }
    dist[x][y] = 0;
    Q.push(x);
    Q.push(y);
    while (!Q.empty())
    {
        int cx = Q.front();
        Q.pop();
        int cy = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (feasible(nx, ny))
            {
                dist[nx][ny] = dist[cx][cy] + 1;
                Q.push(nx);
                Q.push(ny);
            }
        }
    }
    if (dist[tx][ty] == INF)
        cout << "unreachable" << endl;
    else
        cout << dist[tx][ty] << endl;
}
int main()
{
    while (cin >> n >> m)
    {
        Initialize(n, m);
        DFS(n, m, x, y, tx, ty, map, dist);
    }
    return 0;
}