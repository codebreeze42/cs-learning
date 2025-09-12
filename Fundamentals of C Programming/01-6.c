#include <stdio.h>
int main()
{
    int time;
    int h, m, s;
    scanf("%d", &time);
    h = time / 3600;
    if (h >= 24)
        h = h % 24;
    int temp = time % 3600;
    m = temp / 60;
    s = temp % 60;
    printf("%02d:%02d:%02d", h, m, s);
    return 0;
}