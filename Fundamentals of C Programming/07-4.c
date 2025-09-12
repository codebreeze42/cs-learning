#include <stdio.h>
int common(int m, int n)
{
    if (m > n)
    {
        if (m % n != 0)
            return common(n, m % n);
        else
            return n;
    }
    else if (n > m)
    {
        if (n % m != 0)
            return common(m, n % m);
        else
            return m;
    }
    else if (n == m)
        return m;
    return 0;
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d", common(m, n));
    return 0;
}