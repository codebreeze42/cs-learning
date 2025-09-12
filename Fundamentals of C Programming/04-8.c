#include <stdio.h>
int arr[10][10];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            scanf("%d", &x);
            arr[i][j] = x;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            int temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
    int sign2 = 0;
    for (int i = 0; i < n; i++)
    {
        int sign1 = 0;
        if (sign2 == 1)
            printf("\n");
        for (int j = 0; j < n; j++)
        {
            if (sign1 == 1)
                printf(" ");
            printf("%d", arr[i][j]);
            sign1 = 1;
        }
        sign1 = 0;
        sign2 = 1;
    }
    return 0;
}