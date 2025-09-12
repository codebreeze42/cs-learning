#include <stdio.h>
int arr[20];
int p = 0;
int n;
void dfs(int current_sum, int max)
{
    if (current_sum == 0)
    {
        printf("%d=%d", n, arr[0]);
        for (int i = 1; i < p; i++)
        {
            printf("+%d", arr[i]);
        }
        printf("\n");
    }
    for (int i = max; i > 0; i--)
    {
        arr[p++] = i;
        if (current_sum - i >= 0)
            dfs(current_sum - i, i);
        p--;
    }
}
int main()
{
    scanf("%d", &n);
    dfs(n, n - 1);
    return 0;
}