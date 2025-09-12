#include <stdio.h>
void find(int arr[], int i, int n, int m)
{
    if (i == n)
    {
        printf("NULL");
        return;
    }
    if (arr[i] == m)
        printf("%d", i);
    else
        find(arr, i + 1, n, m);
}
int main()
{
    int arr[200];
    int n, m, i = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    find(arr, i, n, m);
    return 0;
}