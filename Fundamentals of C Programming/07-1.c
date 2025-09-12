#include <stdio.h>
int calculate(int m, int n)
{
    if (n < 0)
        return 0;
    else if (n == 0)
        return 1;
    else if (n == 1)
        return m;
    else if (m < 2 * n)
        return calculate(m, m - n);
    else if (m >= 2 * n)
        return calculate(m - 1, n - 1) + calculate(m - 1, n);
    return 0;
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d", calculate(m, n));
    return 0;
}