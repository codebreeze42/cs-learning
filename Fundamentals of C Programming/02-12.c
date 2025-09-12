#include <stdio.h>
int main()
{
    float n;
    scanf("%f", &n);
    float result = 1, num = 1;
    for (int i = 1; i <= 100; i++)
    {
        num = n * num / i;
        result += num;
    }
    printf("%.2f", result);
    return 0;
}