#include <stdio.h>
int main()
{
    int n, flag = 0, count = 1, sign = 1;
    scanf("%d", &n);
    int a[100];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++)
    {
        flag = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[i] == a[j])
                flag = 1;
        }
        if (flag == 0)
        {
            a[count] = a[i];
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (sign == 0)
        {
            printf(" ");
        }
        printf("%d", a[i]);
        sign = 0;
    }
    return 0;
}