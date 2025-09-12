#include <stdio.h>
int main()
{
    long long num, re_num = 0;
    scanf("%lld", &num);
    if (num < 0)
        printf("NULL");
    else
    {
        while (num > 0)
        {
            re_num = re_num * 10 + num % 10;
            num = num / 10;
        }
        printf("%lld", re_num);
    }
    return 0;
}