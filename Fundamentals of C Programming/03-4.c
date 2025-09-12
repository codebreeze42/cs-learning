#include <stdio.h>
#include <math.h>
int main()
{
    long long n;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        long long temp = i * i;
        long long length = log10(i) + 1;
        long long last = temp % (long long)pow(10, length);
        if (last == i)
            printf("%lld ", i);
    }
    return 0;
}