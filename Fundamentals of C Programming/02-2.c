#include <stdio.h>
int main()
{
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    char ch = getchar();
    while (ch != '@')
    {
        if (ch == '(')
            a++;
        else if (ch == ')')
            b++;
        else if (ch == '[')
            c++;
        else if (ch == ']')
            d++;
        else if (ch == '{')
            e++;
        else if (ch == '}')
            f++;
        ch = getchar();
    }
    if (e != f)
        printf("{}");
    if (c != d)
        printf("[]");
    if (a != b)
        printf("()");
    if (a == b && c == d & e == f)
        printf("NULL");
    return 0;
}