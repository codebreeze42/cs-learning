#include <stdio.h>
int arr[1000] = {0};
int main()
{
    int n, s, m;
    scanf("%d %d %d", &n, &s, &m);
    int cur = s - 1, count = m, count2 = n;
    int sign = 0;
    while (count2)
    {
        count2--;
        if (sign == 0)
        {
            while (count - 1)
            {
                cur = (cur + 1) % n;
                if (arr[cur] == 0)
                    count--;
            }
            count = m;
            printf("%d", cur + 1);
            arr[cur] = 1;
            sign = 1;
        }
        else
        {
            while (count)
            {
                cur = (cur + 1) % n;
                if (arr[cur] == 0)
                    count--;
            }
            count = m;
            printf("%d", cur + 1);
            arr[cur] = 1;
        }
        if (count2 > 0)
            printf(" ");
    }
    return 0;
}