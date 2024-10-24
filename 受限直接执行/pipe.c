#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define ITERATIONS 10000  // 迭代次数

int main() {
    int pipe1[2], pipe2[2];
    struct timespec start, end;
    long long elapsed_time;

    // 创建两个管道
    pipe(pipe1);
    pipe(pipe2);

    // 创建子进程
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // 子进程
        for (int i = 0; i < ITERATIONS; i++) {
            char buffer[1];
            // 从父进程读取数据
            read(pipe1[0], buffer, 1);
            // 写回数据到父进程
            write(pipe2[1], "c", 1);
        }
    } else {  // 父进程
        // 测量开始时间
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < ITERATIONS; i++) {
            char buffer[1];
            // 向子进程写数据
            write(pipe1[1], "p", 1);
            // 读取子进程返回的数据
            read(pipe2[0], buffer, 1);
        }

        // 测量结束时间
        clock_gettime(CLOCK_MONOTONIC, &end);

        // 计算经过的纳秒时间
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);

        // 打印结果
        printf("每次上下文切换的平均耗时: %lld 纳秒\n", elapsed_time / (ITERATIONS * 2));

        // 等待子进程结束
        wait(NULL);
    }

    return 0;
}
