#include <stdio.h>
#include <stdbool.h>
int main()
{
    int data;
    bool first = true;
    scanf("%d", &data);
    for (int i = 0; i < data; i += 11)
    {
        if (!first)
            printf(" ");
        printf("%d", i);
        first = false;
    }
    return 0;
}