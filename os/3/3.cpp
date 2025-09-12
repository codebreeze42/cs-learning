#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#define MAPSIZE 100
struct map // 存储资源表结构
{
    int m_addr;
    int m_size;
};
struct map map[MAPSIZE]; // 存储资源表
// BF（最佳适应）存储分配函数
int BF_malloc(struct map *mp, int size)
{
    register int a, s; // 起始地址，内存块大小
    register struct map *bp, *bpp;
    for (bp = mp; bp->m_size; bp++)
    {
        if (bp->m_size >= size)
        {
            a = bp->m_addr;
            s = bp->m_size;
            for (bpp = bp; bpp->m_size; bpp++)
            { // 最佳适应（最小但足够）
                if (bpp->m_size >= size && bpp->m_size < s)
                {
                    a = bpp->m_addr;
                    s = bpp->m_size;
                    bp = bpp;
                }
            }
            // 更新地址
            bp->m_addr += size;
            // 剩余大小为0，删除内存块
            if ((bp->m_size -= size) == 0)
                do
                {
                    bp++;
                    (bp - 1)->m_addr = bp->m_addr;
                } while ((bp - 1)->m_size = bp->m_size);
            return (a);
        }
    }
    return (-1);
}

// WF（最坏适应）存储分配函数
int WF_malloc(struct map *mp, int size)
{
    register int a, s;
    register struct map *bp, *bpp;
    for (bp = mp; bp->m_size; bp++)
    {
        if (bp->m_size >= size)
        {
            a = bp->m_addr;
            s = bp->m_size;
            for (bpp = bp; bpp->m_size; bpp++)
            { // 最坏适应（剩余空间最大的块）
                if (bpp->m_size > s)
                {
                    a = bpp->m_addr;
                    s = bpp->m_size;
                    bp = bpp;
                }
            }
            // 更新地址
            bp->m_addr += size;
            // 剩余大小为0，删除内存块
            if ((bp->m_size -= size) == 0)
                do
                {
                    bp++;
                    (bp - 1)->m_addr = bp->m_addr;
                } while ((bp - 1)->m_size = bp->m_size);
            return (a);
        }
    }
    return (-1);
}

// 存储释放函数
int mfree(struct map *mp, int aa, int size) // aa为起始地址
{
    register struct map *bp;
    register int t;
    register int a;
    a = aa;
    // 检查地址是否合法
    for (bp = mp; bp->m_size; bp++)
    {
        // 空闲块内部
        if (bp->m_addr <= a && bp->m_addr + bp->m_size > a)
        {
            return -1;
        }
        // 重叠
        if (bp->m_addr < aa + size && bp->m_addr + bp->m_size > aa + size)
        {
            return -1;
        }
        // 释放的块包含空闲块
        if (aa <= bp->m_addr && aa + size > bp->m_addr + bp->m_size)
        {
            return -1;
        }
    }
    // 找到第一个地址大于a的空闲块
    for (bp = mp; bp->m_addr <= a && bp->m_size != 0; bp++)
        ;
    // 合并内存块
    // 与前一个合并
    if (bp > mp && (bp - 1)->m_addr + (bp - 1)->m_size == a)
    { //
        (bp - 1)->m_size += size;
        if (a + size == bp->m_addr)
        { // 前后合并
            (bp - 1)->m_size += bp->m_size;
            while (bp->m_size)
            {
                bp++;
                (bp - 1)->m_addr = bp->m_addr;
                (bp - 1)->m_size = bp->m_size;
            }
        }
    }

    else
    {
        if (a + size == bp->m_addr && bp->m_size)
        { // 与后合并
            bp->m_addr -= size;
            bp->m_size += size;
        }
        else if (size)
            do
            { // 无合并
                t = bp->m_addr;
                bp->m_addr = a;
                a = t;
                t = bp->m_size;
                bp->m_size = size;
                bp++;
            } while (size = t);
    }
    return 0;
}
void init()
{
    struct map *bp;
    int addr, size;
    int i = 0;
    bp = map;
    printf("Please input starting addr and total size:");
    scanf("%d,%d", &addr, &size);
    bp->m_addr = addr;
    bp->m_size = size;
    (++bp)->m_size = 0; // 表尾
}

void show_map()
{
    int i = 0;
    // system("clear");  //清屏
    struct map *bp;
    bp = map;
    printf("\nCurrent memory map...\n");
    printf("Address\t\tSize\n");
    while (bp->m_size != 0)
    {
        printf("<%d\t\t%d>\n", bp->m_addr, bp->m_size);
        bp++;
    }
    printf("\n");
}
int main()
{
    int a, s;
    char c;
    int i;
    init();
    printf("please input, b for BF, w for WF,e for exit:");
    getchar();
    scanf("%c", &c);
    do
    {
        show_map(); // 显示存储资源表
        printf("Please input,1 for request,2 for release,0 for exit:");
        scanf("%d", &i);
        switch (i)
        {
        // 申请
        case 1:
            printf("Please input size:");
            scanf("%d", &s);
            if (c == 'b') // BF
                a = BF_malloc(map, s);
            else // WF
                a = WF_malloc(map, s);
            if (a == -1)
                printf("request can't be satisfied\n");
            else
                printf("alloc memory at address:%d,size:%d\n", a, s);
            break;
        // 释放
        case 2:
            printf("Please input addr and size:");
            scanf("%d%d", &a, &s);
            if (mfree(map, a, s) == -1)
            {
                printf("Unallocated Address. Request can't be satisfied\n");
            }
            break;
        case 0:
            exit(0);
        }
    } while (1);
}
