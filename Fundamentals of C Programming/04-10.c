#include <stdio.h>
char arr[255];
int main()
{
    int count = 0;
    char ch;
    while (scanf("%c", &ch) == 1)
    {

        // if (ch == '\n')
        //     break;
        arr[count] = ch;
        // printf("%c", arr[count]);
        count++;
    }
    for (int i = count - 1; i >= 0; i--)
    {
        printf("%c", arr[i]);
    }
    return 0;
}