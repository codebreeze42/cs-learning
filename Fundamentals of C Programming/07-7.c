#include <stdio.h>
int sign = 0;
void reverse(int n, int arr[])
{
    if (n == 0)
        return;
    if (sign == 1)
        printf(" ");
    sign = 1;
    printf("%d", arr[n - 1]);
    reverse(n - 1, arr);
}
int main()
{
    int n, arr[200];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    reverse(n, arr);
    return 0;
}