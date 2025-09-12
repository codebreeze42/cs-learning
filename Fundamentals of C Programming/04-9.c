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
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] != arr[j][i])
            {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");
    return 0;
}