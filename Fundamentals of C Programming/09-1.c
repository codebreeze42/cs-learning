#include <stdio.h>
#include <malloc.h>
struct cell
{
    int x;
    struct cell *next;
};
struct cell *build(void)
{
    struct cell *head, *tmp, *p;
    head = tmp = p = NULL;
    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        tmp = (struct cell *)malloc(sizeof(struct cell));
        tmp->x = n;
        tmp->next = NULL;
        if (head == NULL)
        {
            head = tmp;
        }
        else
        {
            p->next = tmp;
        }
        p = tmp;
        scanf("%d", &n);
    }
    return head;
}
void print(struct cell *head)
{
    int sign = 0;
    while (head != NULL)
    {
        if (sign == 1)
            printf(" ");
        sign = 1;
        printf("%d", head->x);
        head = head->next;
    }
}
void release(struct cell *head)
{
    struct cell *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
int main()
{
    struct cell *head;
    head = build();
    if (head != NULL)
        print(head);
    else
        printf("NULL");
    release(head);
}