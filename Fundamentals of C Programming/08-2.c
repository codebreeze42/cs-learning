#include <stdio.h>
#include <stdlib.h>
int arr[20] = {0};
int count = 0;
int feasible(int k, int i)
{
    for (int j = 1; j <= k - 1; j++)
    {
        if (arr[j] == i || abs(k - j) == abs(arr[j] - i))
            return 0;
    }
    return 1;
}
int nQueens(int n, int k)
{
    if (k > n)
        count++;
    for (int i = 1; i <= n; i++)
    {
        if (feasible(k, i))
        {
            arr[k] = i;
            nQueens(n, k + 1);
        }
    }
    return count;
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", nQueens(n, 1));
    return 0;
}