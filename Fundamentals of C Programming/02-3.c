#include <stdio.h>
int main()
{
    int a, sum = 0, a1, a2, a3, a4, a5;
    scanf("%d %d %d %d %d %d", &a, &a1, &a2, &a3, &a4, &a5);
    if (a1 % a == 0)
        sum += a1;
    if (a2 % a == 0)
        sum += a2;
    if (a3 % a == 0)
        sum += a3;
    if (a4 % a == 0)
        sum += a4;
    if (a5 % a == 0)
        sum += a5;
    printf("%d", sum);
    return 0;
}