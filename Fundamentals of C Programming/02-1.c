#include <stdio.h>
int main()
{
    float max, sub, min;
    scanf("%f %f %f", &max, &sub, &min);
    if (max > sub)
        ;
    else
    {
        float temp = max;
        max = sub;
        sub = temp;
    }
    if (max > min)
        ;
    else
    {
        float temp = max;
        max = min;
        min = temp;
    }
    if (sub > min)
        ;
    else
    {
        float temp = sub;
        sub = min;
        min = temp;
    }
    printf("%.1f %.1f %.1f", min, sub, max);
    return 0;
}