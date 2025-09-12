#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char *str_delete(char *s, int v, int w)
{

    int n = strlen(s);
    //    printf("%d",v+w-1);
    //    printf("%c",s[0]);
    //    printf("%c",s[v+w-1]);
    for (int i = v + w - 1; i < n; i++)
    {
        // printf("%c",s[i]);

        s[i - w] = s[i];
    }

    return s;
}

int main()

{

    int v, w;

    char arr[256];

    scanf("%d %d\n", &v, &w);

    getchar();
    gets(arr);

    char *s = str_delete(arr, v, w);
    int len = strlen(arr);
    int len2 = strlen(s);

    // printf("%s",s);
    int i = 0;
    while (i < len - w)
    {
        printf("%c", s[i++]);
    }

    return 0;
}
