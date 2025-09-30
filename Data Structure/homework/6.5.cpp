#include <iostream>
using namespace std;
struct Edge
{
    int VerAdj;
    Edge *link;
};
struct vertex
{
    int verName;
    Edge *adjacent;
};
vertex graph[2000];
int visited[2000] = {0};
int dist[2000] = {0};
void dfs(int node, int parent, int &farthestnode, int &maxdist)
{
    if (parent == -1)
    {
        dist[node] = 0;
    }
    else
    {
        dist[node] = dist[parent] + 1;
    }
    if (dist[node] > maxdist)
    {
        maxdist = dist[node];
        farthestnode = node;
    }
    for (Edge *edge = graph[node].adjacent; edge != nullptr; edge = edge->link)
    {
        if (edge->VerAdj != parent)
        {
            dfs(edge->VerAdj, node, farthestnode, maxdist);
        }
    }
}