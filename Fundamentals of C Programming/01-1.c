#include <stdio.h>
#include <math.h>
float a, x, y = 0;
const float PI = 3.1415926;
int main()
{
    scanf("%f %f", &a, &x);
    y = sin(x) / a / x + fabs(cos(PI * x / 2));
    printf("%.3f", y);
    return 0;
}
