#include <stdio.h>
#include <stdlib.h>
void count(char *str, int *upper, int *lower, int *space, int *num, int *other)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            (*upper)++;
        else if (str[i] >= 'a' && str[i] <= 'z')
            (*lower)++;
        else if (str[i] == ' ')
            (*space)++;
        else if (str[i] >= '0' && str[i] <= '9')
            (*num)++;
        else
            (*other)++;
        i++;
    }
}
int main()
{
    char arr[256];
    gets(arr);
    int upper = 0, lower = 0, space = 0, num = 0, other = 0;
    count(arr, &upper, &lower, &space, &num, &other);
    printf("%d %d %d %d %d", upper, lower, space, num, other);
    return 0;
}
