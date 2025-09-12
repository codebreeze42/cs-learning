#include <stdio.h>
#include <stdlib.h>
int arr[92][9];
int count = 0;
int a[9];
int feasible(int k, int i)
{
    for (int j = 1; j < k; j++)
    {
        if (a[j] == i || abs(j - k) == abs(a[j] - i))
            return 0;
    }
    return 1;
}
void nQueens(int k)
{
    if (k >= 9)
    {
        for (int i = 1; i < 9; i++)
        {
            arr[count][i] = a[i];
        }
        count++;
        return;
    }
    for (int i = 1; i < 9; i++)
    {
        if (feasible(k, i))
        {
            a[k] = i;
            nQueens(k + 1);
            a[k] = 0;
        }
    }
}
int check(int a1[], int a2[])
{
    int sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a1[i] + a2[i] != 9)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a1[i] != a2[9 - i])
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a2[a1[i]] != i)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a2[9 - a1[i]] != 9 - i)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a1[i] + a2[9 - i] != 9)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a2[9 - a1[i]] != i)
        {
            sign = 1;
            break;
        }
    }
    if (sign == 0)
        return sign;
    sign = 0;
    for (int i = 1; i <= 8; i++)
    {
        if (a2[a1[i]] != 9 - i)
        {
            sign = 1;
            break;
        }
    }
    return sign;
}
int main()
{
    int flag = 1, num = 1, first = 1;
    nQueens(1);
    // for (int i = 0; i < 92; i++)
    // {
    //     for (int k = 1; k <= 8; k++)
    //     {
    //         printf("%d ", arr[i][k]);
    //     }
    //     printf("\n");
    // }
    for (int i = 0; i < 92; i++)
    {

        for (int j = i - 1; j >= 0; j--)
        {
            if (!check(arr[i], arr[j]))
                flag = 0;
        }
        if (flag == 1)
        {
            if (first == 0)
                printf("\n");
            first = 0;
            printf("No%d:", num++);
            for (int k = 1; k <= 8; k++)
            {
                printf("%d ", arr[i][k]);
            }
        }
        flag = 1;
    }
    return 0;
}