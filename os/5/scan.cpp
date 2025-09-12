#include <stdio.h>
#include <stdlib.h>

// SCAN 算法的核心函数
int SCAN(int *cyc_list, int *cyc_order, int n, int start, int dir)
{
    int sum, max_int, min_value, index, tag[100] = {0};
    sum = 0;
    int x_max = cyc_list[0], x_min = cyc_list[0];
    for (int i = 1; i < n; i++)
    {
        if (cyc_list[i] > x_max)
        {
            x_max = cyc_list[i];
        }
        if (cyc_list[i] < x_min)
        {
            x_min = cyc_list[i];
        }
    }
    int turn = 0;
    for (int i = 0; i < n; i++)
    {
        max_int = 9999;
        for (int j = 0; j < n; j++)
        {
            if (dir == 1 && cyc_list[j] > start && tag[j] == 0)
            {
                // cyc_list表示待执行柱面
                min_value = cyc_list[j] - start;
                if (min_value < max_int)
                {
                    max_int = min_value;
                    index = j; // 记录距离最小的待执行柱面号的索引
                }
            }
            else if (dir == 0 && cyc_list[j] < start && tag[j] == 0)
            {
                min_value = abs(cyc_list[j] - start);
                if (min_value < max_int)
                {
                    max_int = min_value;
                    index = j; // 记录距离最小的待执行柱面号的索引
                }
            }
        }
        // 判断是否需要转向

        if (dir == 1 && turn == 0 && cyc_list[index] == x_max)
        {
            dir = 0;
            if (i != n - 1)
                sum += 2 * (500 - x_max);
            turn = 1;
        }
        else if (turn == 0 && cyc_list[index] == x_min)
        {
            dir = 1;
            if (i != n - 1)
                sum += 2 * x_min;
        }
        sum += max_int; // 累积磁头移动轨道数
        tag[index] = 1;
        cyc_order[i] = cyc_list[index];
        start = cyc_list[index];
    }
    return sum;
}

// SCAN
void main()
{
    int cyc_list[100], cyc_order[100], n, start, dir, ans = 0;
    printf("请输入磁臂初始移动方向（1向内，0向外）："); // 1向大数走，0向小数走
    scanf("%d", &dir);
    printf("请输入初始柱面和待执行柱面数量：");
    scanf("%d%d", &start, &n);
    printf("请输入待执行柱面：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cyc_list[i]);
    }
    ans = SCAN(cyc_list, cyc_order, n, start, dir);
    printf("SCAN走道顺序为：");
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
}