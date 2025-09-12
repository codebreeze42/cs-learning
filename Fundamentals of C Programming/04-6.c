#include <stdio.h>
int arr[100];
int main()
{
    int n, m, move, sign = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        arr[i] = x;
    }
    move = m % n;

    for (int i = 0; i < move; i++)
    {
        int current = arr[0];
        for (int i = 0; i < n; i++)
        {
            int temp = arr[(i + 1) % n];
            arr[(i + 1) % n] = current;
            current = temp;
        }
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