#include <stdio.h>
#include <stdbool.h>
char stack[1000] = {0};
int top = -1;
void push(int x)
{
    stack[++top] = x;
}
int pop()
{
    return stack[top--];
}

bool isInvalid(char x, char y)
{
    char pair[200] = {0};
    pair['('] = ')';
    pair['['] = ']';
    pair['{'] = '}';
    if (pair[x] == y)
        return true;
    else
        return false;
}
int main()
{

    char x;
    while (1)
    {
        scanf("%c", &x);
        if (x == '@')
        {
            printf("YES");
            return 0;
        }
        else if (x == '(' || x == '{' || x == '[')
        {
            push(x);
        }
        else if (x == ')' || x == '}' || x == ']')
        {
            char y = pop();
            if (!isInvalid(y, x))
            {
                printf("NO");
                break;
            }
        }
    }
    return 0;
}