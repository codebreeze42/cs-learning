#define _GNU_SOURCE // 用于启用clone()等GNU特定功能
#include "sched.h"
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "semaphore.h"
#include <string.h>
#include <unistd.h> // 添加sleep()函数声明
int producer(void *args);
int consumer(void *args);
pthread_mutex_t mutex; // 互斥锁，用于保护共享资源
sem_t product;         // 产品信号量(初始为0)
sem_t warehouse;       // 仓库容量信号量(初始为8)
char buffer[8][4];     // 8个位置的缓冲区，每个位置可存4字节字符串
int bp = 0;            // 缓冲区指针，指示下一个可用位置
int main(int argc, char **argv)
{
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁
    sem_init(&product, 0, 0);         // 产品信号量初始值为0
    sem_init(&warehouse, 0, 8);       // 仓库信号量初始值为8(缓冲区大小)
    int clone_flag, arg, retval;
    char *stack;
    clone_flag = CLONE_VM | CLONE_SIGHAND | CLONE_FS | CLONE_FILES;
    int i;
    for (i = 0; i < 2; i++)
    {
        int *producer_arg = malloc(sizeof(int));
        *producer_arg = i;
        stack = (char *)malloc(4096);
        clone((void *)producer, stack + 4096, clone_flag, producer_arg);

        int *consumer_arg = malloc(sizeof(int));
        *consumer_arg = i;
        stack = (char *)malloc(4096);
        clone((void *)consumer, stack + 4096, clone_flag, consumer_arg);
    }
    sleep(1000);
    exit(1);
}
int producer(void *args)
{
    int id = *((int *)args); // 获取生产者ID(0或1)
    int i;
    for (i = 0; i < 10; i++)
    {
        sleep(i + 1);               // 表现线程速度差别
        sem_wait(&warehouse);       // 等待仓库有空位(减少仓库信号量)
        pthread_mutex_lock(&mutex); // 获取互斥锁
        // 生产产品
        if (id == 0)
            strcpy(buffer[bp], "aaa\0");
        else
            strcpy(buffer[bp], "bbb\0");
        bp++; // 移动缓冲区指针
        printf("producer%d produce %s in %d\n", id, buffer[bp - 1], bp - 1);
        pthread_mutex_unlock(&mutex); // 释放互斥锁
        sem_post(&product);           // 增加产品信号量
    }
    printf("producer%d is over!\n", id);
}
int consumer(void *args)
{
    int id = *((int *)args); // 获取消费者ID(0或1)
    int i;
    for (i = 0; i < 10; i++)
    {
        sleep(10 - i);              // 表现线程速度差别, 模拟消费速度逐渐变快
        sem_wait(&product);         // 等待有产品可消费(减少产品信号量)
        pthread_mutex_lock(&mutex); // 获取互斥锁
        bp--;                       // 移动缓冲区指针
        printf("consumer%d get %s in%d\n", id, buffer[bp], bp);
        strcpy(buffer[bp], "zzz\0");  // 消费产品(标记为zzz)
        pthread_mutex_unlock(&mutex); // 释放互斥锁
        sem_post(&warehouse);         // 增加仓库信号量(释放一个位置)
    }
}
