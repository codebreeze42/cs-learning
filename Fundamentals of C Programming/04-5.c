#include <stdio.h>
int arr[100];
int main()
{
    int n, zero = 0, cur = 0, x, sign = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        if (x == 0)
            zero++;
        else
        {
            arr[cur] = x;
            cur++;
        }
    }
    for (int i = cur; i < n; i++)
    {
        arr[cur] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (sign == 1)
            printf(" ");
        printf("%d", arr[i]);
        sign = 1;
    }
    return 0;
}
