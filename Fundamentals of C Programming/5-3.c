#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    int arr[2500];
    scanf("%d %d", &n, &m);
    int num = n * m;
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i < num; i++)
    {
        int j = i - 1;
        int k = arr[i];
        while (j >= 0 && arr[j] > k)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
    int sign = 0, k = 0, flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (sign == 1)
            printf("\n");
        sign = 1;
        for (int j = 0; j < m; j++)
        {
            if (flag == 1)
                printf(" ");
            flag = 1;
            printf("%d", arr[k++]);
        }
        flag = 0;
    }
    return 0;
}
