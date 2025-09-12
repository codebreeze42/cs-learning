#include <stdio.h>
int main()
{
    long long big = 0, small = 1, sum = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        long long temp = big;
        big = big + small;
        small = temp;
        sum = big + small;
    }
    printf("%lld", sum);
    return 0;
}