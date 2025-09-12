#include <stdio.h>
int main()
{
    int n;
    char *one1[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *ten1[10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char *ten2[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    scanf("%d", &n);
    if (n < 0 || n >= 1000)
    {
        printf("ERR");
        return 0;
    }
    if (n == 0)
        printf("zero");
    int h = n % 1000 / 100, ten = n % 100 / 10, one = n % 10;
    if (h != 0)
    {
        printf("%s ", one1[h]);
        if (ten != 0 || one != 0)
        {
            printf("hundred and ");
        }
        else
            printf("hundred");
    }
    if (ten == 1)
    {
        printf("%s", ten2[one]);
    }
    if (ten > 1)
    {
        printf("%s", ten1[ten]);
        if (one != 0)
        {
            printf("-");
            printf("%s", one1[one]);
        }
    }
    if (ten == 0 && one != 0)
        printf("%s", one1[one]);
    return 0;
}