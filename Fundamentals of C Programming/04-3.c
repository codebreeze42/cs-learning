#include <stdio.h>
#include <string.h>
void pivot(int a[])
{
    int b[10];
    int com_p = 0, mov_p = 0;
    memcpy(b, a, 40);
    for (int i = 0; i < 9; i++)
    {
        int k = i;
        for (int j = i + 1; j < 10; j++)
        {
            com_p++;
            if (b[j] < b[k])
                k = j;
        }
        int temp = b[k];
        b[k] = b[i];
        b[i] = temp;
        mov_p++;
    }
    printf("%d %d ", com_p, mov_p);
}
void bubble(int a[])
{
    int b[10];
    int com_b = 0, mov_b = 0, flag = 1;
    memcpy(b, a, 40);
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < 9; i++)
        {
            com_b++;
            if (b[i] > b[i + 1])
            {
                int temp = b[i];
                b[i] = b[i + 1];
                b[i + 1] = temp;
                mov_b++;
                flag = 1;
            }
        }
    }
    printf("%d %d ", com_b, mov_b);
}
void insert(int a[])
{
    int b[10];
    int com_i = 0, mov_i = 0;
    memcpy(b, a, 40);
    for (int i = 1; i < 10; i++)
    {
        int key = b[i];
        int j = i - 1;
        while (j >= 0 && b[j] > key)
        {
            b[j + 1] = b[j];
            j--;
            com_i++;
            mov_i++;
        }
        b[j + 1] = key;
        if (j != i - 1)
            mov_i++;
    }
    com_i += 9;
    printf("%d %d", com_i, mov_i);
}
int main()
{
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &a[i]);
    }
    pivot(a);
    bubble(a);
    insert(a);
    return 0;
}