#include <stdio.h>
float calculate(int n, float x)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return 2 * x;
    else if (n > 1)
        return 2 * x * calculate(n - 1, x) - 2 * (n - 1) * calculate(n - 2, x);
    return 0;
}
int main()
{
    int n;
    float x;
    scanf("%d %f", &n, &x);
    float num = calculate(n, x);
    printf("%.2f", num);
    return 0;
}