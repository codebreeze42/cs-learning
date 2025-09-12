#include <stdio.h>
#include <stdbool.h>
bool isPrime(int x)
{
    for (int i = 2; i < x; i++)
    {
        int temp = x % i;
        if (temp == 0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    int num;
    scanf("%d", &num);
    if (isPrime(num))
        printf("Y");
    else
        printf("N");
    return 0;
}