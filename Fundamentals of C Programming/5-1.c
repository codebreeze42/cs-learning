#include <stdio.h>
int strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}
int main()
{
    char arr[256];
    gets(arr);
    int len = strlen(arr);
    printf("%d", len);
    return 0;
}