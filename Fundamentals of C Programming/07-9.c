#include <stdio.h>
void base(long long n, int b)
{
    if (n < b)
    {
        if (n < 10)
            printf("%c", n + '0');
        else
            printf("%c", n % 10 + 'A');
        return;
    }
    else
    {
        base(n / b, b);
        if (n % b < 10)
            printf("%c", n % b + '0');
        else
            printf("%c", n % b % 10 + 'A');
    }
}
int main()
{
    long long n;
    int b;
    scanf("%lld %d", &n, &b);
    base(n, b);
    return 0;
}