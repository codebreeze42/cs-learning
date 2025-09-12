#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    double num = 0, den = 0;
    double result = 1;
    for (int i = 1; i <= n; i++)
    {
        num = 2 * i;
        den = 2 * i - 1;
        result *= num / den;
        den = 2 * i + 1;
        result *= num / den;
    }
    result = result * 2;
    printf("%.10lf", result);
    return 0;
}