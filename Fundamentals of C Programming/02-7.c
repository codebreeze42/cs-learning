#include <stdio.h>
int main()
{
    int count;
    int first = 0;
    scanf("%d", &count);
    if (count % 3 == 0)
    {
        first = 1;
        printf("3");
    }
    if (count % 5 == 0)
    {

        if (first)
            printf(",");
        printf("5");
        first = 1;
    }

    if (count % 7 == 0)
    {
        if (first)
            printf(",");
        printf("7");
        first = 1;
    }
    if (first == 0)
        printf("NULL");
    return 0;
}