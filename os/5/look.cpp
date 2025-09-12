#include <stdio.h>
#include <stdlib.h>
#include <math.h> // 为了使用 abs()

// LOOK 算法的核心函数
int LOOK(int *cyc_list, int *cyc_order, int n, int start, int dir)
{
    int sum = 0;
    int x_max = cyc_list[0], x_min = cyc_list[0];
    for (int i = 1; i < n; i++)
    {
        if (cyc_list[i] > x_max)
            x_max = cyc_list[i];
        if (cyc_list[i] < x_min)
            x_min = cyc_list[i];
    }

    int turn = 0;
    int tag[100] = {0}; // 标记是否访问过柱面

    for (int i = 0; i < n; i++)
    {
        int max_int = 9999;
        int index = -1;

        for (int j = 0; j < n; j++)
        {
            if (dir == 1 && cyc_list[j] > start && tag[j] == 0)
            {
                int diff = cyc_list[j] - start;
                if (diff < max_int)
                {
                    max_int = diff;
                    index = j;
                }
            }
            else if (dir == 0 && cyc_list[j] < start && tag[j] == 0)
            {
                int diff = abs(cyc_list[j] - start);
                if (diff < max_int)
                {
                    max_int = diff;
                    index = j;
                }
            }
        }

        // 如果当前方向找不到下一个请求，则转向
        if (index == -1)
        {
            if (dir == 1)
            {
                dir = 0;
                turn = 1;
            }
            else
            {
                dir = 1;
                turn = 1;
            }

            // 再次查找反向最近的请求
            for (int j = 0; j < n; j++)
            {
                if (dir == 1 && cyc_list[j] < start && tag[j] == 0)
                {
                    int diff = start - cyc_list[j];
                    if (diff < max_int)
                    {
                        max_int = diff;
                        index = j;
                    }
                }
                else if (dir == 0 && cyc_list[j] > start && tag[j] == 0)
                {
                    int diff = cyc_list[j] - start;
                    if (diff < max_int)
                    {
                        max_int = diff;
                        index = j;
                    }
                }
            }
        }

        sum += max_int;
        tag[index] = 1;
        cyc_order[i] = cyc_list[index];
        start = cyc_list[index];
    }

    return sum;
}

// 主函数
int main()
{
    int cyc_list[100], cyc_order[100], n, start, dir, ans = 0;
    printf("请输入磁臂初始移动方向（1向内，0向外）："); // 1: 增大方向，0: 减小方向
    scanf("%d", &dir);
    printf("请输入初始柱面和待执行柱面数量：");
    scanf("%d%d", &start, &n);
    printf("请输入待执行柱面：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cyc_list[i]);
    }

    ans = LOOK(cyc_list, cyc_order, n, start, dir);

    printf("LOOK走道顺序为：");
    for (int i = 0; i < n; i++)
    {
        printf("%d", cyc_order[i]);
        if (i + 1 != n)
        {
            printf(" -> ");
        }
    }
    printf("\n");

    printf("磁头走过总道数为：%d\n", ans);
    float res = (float)ans / n;
    printf("平均寻道长度: %.1f\n", res);

    return 0;
}