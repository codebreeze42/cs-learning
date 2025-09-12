#include <stdio.h>
int main()
{
    char cur;
    scanf("%c", &cur);
    printf("%c%c%c", cur - 1, cur, cur + 1);
    return 0;
}