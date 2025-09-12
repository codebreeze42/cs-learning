#include <stdio.h>
#include <string.h>
int isvalid(char *arr, int len)
{
    if (arr[0] == '_' || (arr[0] >= 'a' && arr[0] <= 'z') || (arr[0] >= 'A' && arr[0] <= 'Z'))
    {
        for (int i = 1; i < len; i++)
        {
            if (arr[i] == '_' || (arr[i] >= '0' && arr[i] <= '9') || (arr[i] >= 'a' && arr[i] <= 'z') || arr[i] >= 'A' && arr[i] <= 'Z')
                ;

            else
            {
                return 0;
            }
        }
        return 1;
    }
    else
        return 0;
}

int main()
{
    int n, valid = 0, invalid = 0;
    char arr[270];
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        gets(arr);
        int len = strlen(arr);
        if (isvalid(arr, len))
            valid++;
        else
            invalid++;
    }
    printf("Valid:%d\n", valid);
    printf("Invalid:%d", invalid);
    return 0;
}