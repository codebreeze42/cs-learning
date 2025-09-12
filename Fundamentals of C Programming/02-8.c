#include <stdio.h>
int main()
{
    int first = 1;
    for (int i = 100; i <= 999; i++)
    {
        int a = i / 100;
        int b = (i % 100) / 10;
        int c = i % 10;
        if (i == a * a * a + b * b * b + c * c * c)
        {
            if (first)
            {
                printf("%d", i);
                first = 0;
            }
            else
                printf(" %d", i);
        }
    }
    return 0;
}
