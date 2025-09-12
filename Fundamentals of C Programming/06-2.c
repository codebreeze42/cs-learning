#include <stdio.h>
#include <stdbool.h>
#include <string.h>
struct teacher
{
    char name[50];
    int genter;
    int age;
};
int main()
{
    int n;
    scanf("%d", &n);
    struct teacher arr[20];
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d %d", &arr[i].name, &arr[i].genter, &arr[i].age);
    }
    int num = n / 2;
    printf("%s ", arr[num].name);
    if (arr[num].genter)
        printf("Male");
    else
        printf("Female");
    printf(" %d", arr[num].age);
    return 0;
}