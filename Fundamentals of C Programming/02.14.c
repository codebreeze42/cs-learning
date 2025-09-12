#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            printf("  ");
        }
        for (int j = 1; j <= i; j++)
        {
            if (j == 10)
                printf(" 0");
            else
                printf(" %d", j);
        }
        for (int j = i - 1; j > 0; j--)
        {
            printf(" %d", j);
        }
        // for (int j = 1; j <= n - i; j++)
        // {
        //     printf("  ");
        // }
        printf("\n");
    }
    return 0;
}