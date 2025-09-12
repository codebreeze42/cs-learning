#include <stdio.h>  // 添加：用于printf函数
#include <stdlib.h> // 添加：用于exit函数
#include <string.h> // 添加：用于strcpy函数
#include "sys/types.h"
#include "sys/file.h"
#include <sys/wait.h> // 添加：用于wait函数
#include "unistd.h"

char r_buf[4];                // 读缓冲区
char w_buf[4];                // 写缓冲区
int pipe_fd[2];               // 管道文件描述符数组
pid_t pid1, pid2, pid3, pid4; // 四个子进程的PID
int producer(int id);
int consumer(int id);

int main(int argc, char **argv)
{
    // 1. 创建管道
    if (pipe(pipe_fd) < 0)
    { // 检查管道是否创建成功
        printf("pipe create error \n");
        exit(-1);
    }
    else
    {
        printf("pipe is created successfully!\n");

        // 2. 创建2个生产者子进程，子进程返回值为0
        if ((pid1 = fork()) == 0)
            producer(1);
        if ((pid2 = fork()) == 0)
            producer(2);

        // 3. 创建2个消费者子进程
        if ((pid3 = fork()) == 0)
            consumer(1);
        if ((pid4 = fork()) == 0)
            consumer(2);
    }

    // 4. 主进程关闭管道两端
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // 5. 等待所有子进程结束
    int i, pid, status;
    for (i = 0; i < 4; i++)
        pid = wait(&status);

    exit(0);
}

int producer(int id)
{
    printf("producer %d is running!\n", id);
    close(pipe_fd[0]); // 关闭读端，生产者只写

    int i = 0;
    for (i = 1; i < 10; i++)
    {
        sleep(3); // 模拟生产耗时

        // 根据ID设置不同的数据
        if (id == 1)
            strcpy(w_buf, "aaa\0");
        else
            strcpy(w_buf, "bbb\0");

        // 写入管道
        if (write(pipe_fd[1], w_buf, 4) == -1)
            printf("write to pipe error\n");
    }

    close(pipe_fd[1]); // 关闭写端
    printf("producer %d is over!\n", id);
    exit(id);
}

int consumer(int id)
{
    close(pipe_fd[1]); // 关闭写端，消费者只读
    printf("consumer %d is running!\n", id);

    // 设置不同的w_buf
    if (id == 1)
        strcpy(w_buf, "ccc\0");
    else
        strcpy(w_buf, "ddd\0");

    while (1)
    {
        sleep(1);               // 模拟消费耗时
        strcpy(r_buf, "eee\0"); // 初始化缓冲区

        // 尝试从管道读取
        if (read(pipe_fd[0], r_buf, 4) == 0)
            break; // 读到EOF(管道写端全部关闭)时退出循环

        printf("consumer %d get %s, while the w_buf is %s\n", id, r_buf, w_buf);
    }

    close(pipe_fd[0]);
}