#include <stdio.h>
void calculate(int arr[], int size, int n)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == n * arr[j] || arr[j] == n * arr[i])
                count++;
        }
    }
    printf("%d", count);
}
int main()
{
    int n, firstline = 1;
    scanf("%d", &n);
    int arr[100];
    int size = 0;
    while (1)
    {
        size = 0;
        while (1)
        {

            int num;
            scanf("%d", &num);
            if (num == -1)
                return 0;
            else if (num == 0)
                break;
            else
            {
                arr[size++] = num;
                // printf("%d", size);
            }
        }
        if (firstline == 0)
            printf("\n");
        // printf("%d", size);
        calculate(arr, size, n);
        firstline = 0;
    }
}