#include <stdio.h>
int main()
{
    int i = 1;
    while (1)
    {
        if (i % 2 == 1 && i % 3 == 2 && i % 5 == 4 && i % 7 == 0)
        {
            printf("%d", i);
            break;
        }
        i++;
    }
    return 0;
}