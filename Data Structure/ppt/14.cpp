struct Vertex
{
    int VerName;
    Edge *adjacent;
};
struct Edge
{
    int VerAdj; // 邻接顶点的序号
    int weight;
    Edge *link;
};
// 统计顶点的入度
void getInDegree(Vertex Head[], int n, int InDegree[])
{
    for (int i = 0; i < n; i++)
        InDegree[i] = 0;
    for (int i = 0; i < n; i++)
        for (Edge *p = Head[i].adjacent; p != nullptr; p = p->link)
        {
            int k = p->VerAdj;
            InDegree[k]++;
        }
}