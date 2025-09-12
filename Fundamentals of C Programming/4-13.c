#include <stdio.h>
int main()
{
    int n, num = 1;
    int sign = 0;
    scanf("%d", &n);
    const int N = n;
    int arr[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr[i][j] = 0;
        }
    }
    int top = 0, left = 0, right = n - 1, bottom = n - 1;
    while (num <= n * n)
    {
        for (int i = left; i <= right && num <= n * n; i++)
        {
            arr[top][i] = num++;
            // printf("%d", num);
        }
        top++;
        for (int i = top; i <= bottom && num <= n * n; i++)
        {
            arr[i][right] = num++;
            // printf("%d", num);
        }
        right--;
        for (int i = right; i >= left && num <= n * n; i--)
        {
            arr[bottom][i] = num++;
            // printf("%d", num);
        }
        bottom--;
        for (int i = bottom; i >= top && num <= n * n; i--)
        {
            arr[i][left] = num++;
            // printf("%d", num);
        }
        left++;
    }
    for (int i = 0; i < n; i++)
    {
        if (sign == 1)
            printf("\n");
        for (int j = 0; j < n; j++)
        {
            printf("%4d", arr[i][j]);
        }
        sign = 1;
    }
    return 0;
}