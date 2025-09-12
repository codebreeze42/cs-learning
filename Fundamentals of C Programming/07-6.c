#include <stdio.h>
int max(int x, int y)
{
    return (x > y) ? x : y;
}
int findmax(int n, int arr[])
{
    if (n == 1)
        return arr[0];
    return max(arr[n - 1], findmax(n - 1, arr));
}
int main()
{
    int n, arr[200];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int max = findmax(n, arr);
    printf("%d", max);
    return 0;
}