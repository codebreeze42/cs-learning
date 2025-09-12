#include <stdio.h>
double pxn(double n, double x)
{
    if (n == 0)
        return 1.0;
    else if (n == 1)
        return x;
    else
    {
        double result = pxn(n - 1, x) * x * (2 * n - 1) / n - (n - 1) / n * pxn(n - 2, x);
        return result;
    }
}
int main()
{
    double n;
    double x;
    scanf("%lf %lf", &x, &n);
    double result = pxn(n, x);
    printf("%.2lf", result);
    return 0;
}