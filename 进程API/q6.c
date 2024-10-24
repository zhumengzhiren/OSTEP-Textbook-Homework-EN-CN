#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // 创建子进程

    if (pid < 0) {
        // fork() 失败
        printf("fork() failed!\n");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("子进程开始执行...\n");
        sleep(2);  // 模拟子进程的工作
        printf("子进程完成。\n");
        exit(0);  // 子进程退出
    } else {
        // 父进程
        printf("父进程等待子进程完成...\n");
        int status;
        pid_t wait_ret = waitpid(pid, &status, 0);  // 等待特定子进程完成

        if (wait_ret > 0) {
            printf("父进程捕获到子进程 %d 结束，返回状态 %d。\n", wait_ret, WEXITSTATUS(status));
        } else {
            printf("父进程调用 waitpid() 失败。\n");
        }
    }

    return 0;
}
