#include <stdio.h>
struct plural
{
    float r_part;
    float i_part;
};
void output(float r, float i)
{
    if (i > 0)
        printf("%.2f+%.2fi", r, i);
    else if (i < 0)
        printf("%.2f-%.2fi", r, -i);
    else
        printf("%.2f", r);
}
int main()
{
    struct plural x;
    struct plural y;
    scanf("%f %f %f %f", &x.r_part, &x.i_part, &y.r_part, &y.i_part);
    float plus_r = x.r_part + y.r_part;
    float plus_i = x.i_part + y.i_part;
    output(plus_r, plus_i);
    printf("    ");
    float sub_r = x.r_part - y.r_part;
    float sub_i = x.i_part - y.i_part;
    output(sub_r, sub_i);
    printf("    ");
    float mul_r = x.r_part * y.r_part - x.i_part * y.i_part;
    float mul_i = x.i_part * y.r_part + x.r_part * y.i_part;
    output(mul_r, mul_i);
    return 0;
}