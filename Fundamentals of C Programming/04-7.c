#include <stdio.h>
int arr[10][10];
int temp[100];
int main()
{
    int n, count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            scanf("%d", &x);
            arr[i][j] = x;
            temp[count] = x;
            count++;
            for (int k = 0; k < count - 1; k++)
            {
                if (temp[k] == arr[i][j])
                {
                    printf("YES");
                    return 0;
                }
            }
        }
    }
    printf("NO");
    return 0;
}