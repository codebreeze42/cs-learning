#include <stdio.h>
int cut(int n, int k)
{
    if (n <= k)
        return 1;
    return cut(n * 2 / 5, k) + cut(n - n * 2 / 5, k); // return cut((double)n*2/5+0.5,k)+cut((double)n*3/5+0.5,k);
}
int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int m = cut(n, k);
    printf("%d", m);
    return 0;
}