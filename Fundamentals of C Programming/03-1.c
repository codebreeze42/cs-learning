#include <stdio.h>
long long factorial(long long x)
{
    long long result = 1;
    for (int i = 1; i <= x; i++)
    {
        result *= i;
    }
    return result;
}
int main()
{
    int m, n, result = 0;
    scanf("%d %d", &m, &n);
    if (m < n && m > 0 && n > 0)
        printf("0");
    else if (m == n && m > 0 && n > 0)
        printf("1");
    else if (m > n && m > 0 && n > 0)
    {
        result = factorial(m) / factorial(m - n) / factorial(n);
        printf("%d", result);
    }
    else
        printf("-1");
    return 0;
}