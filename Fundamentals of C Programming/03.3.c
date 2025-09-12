#include <stdio.h>
#include <math.h>
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
}
int main()
{
    int n;
    double result = 0;
    scanf("%d", &n);
    double x[10], y[10];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &x[i]);
        scanf("%lf", &y[i]);
    }
    if (n == 1)
        printf("0.00");
    else if (n == 2)
    {
        result = distance(x[0], y[0], x[1], y[1]);
        printf("%.2f", result);
    }
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            result += distance(x[i], y[i], x[i + 1], y[i + 1]);
        }
        result += distance(x[n - 1], y[n - 1], x[0], y[0]);
        printf("%.2f", result);
    }
    return 0;
}
