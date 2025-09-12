#include <stdio.h>
int main()
{
    float x, y;
    scanf("%f", &x);
    y = 1 + 1 / (1 + 1 / (1 + 1 / (1 + 1 / (1 + 1 / x))));
    printf("%.3f", y);
    return 0;
}