#include <stdio.h>
int Ack(int m, int n)
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return Ack(m - 1, 1);
    else if (m > 0 && n > 0)

        return Ack(m - 1, Ack(m, n - 1));
    return 0;
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    printf("%d", Ack(m, n));
    return 0;
}