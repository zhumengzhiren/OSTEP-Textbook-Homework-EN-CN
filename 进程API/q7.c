#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // 创建子进程

    if (pid < 0) {
        // fork() 失败
        printf("fork() 失败\n");
        return 1;
    } else if (pid == 0) {
        // 子进程
        printf("子进程：准备关闭标准输出...\n");
        for (int i = 0; i < 3; i++) {
            sleep(1);
            printf("子进程：倒计时 %d 秒...\n", 3 - i);
        }
        close(STDOUT_FILENO);  // 关闭标准输出
        printf("子进程：这段文字不会显示在终端上\n");  // 无法输出
    } else {
        // 父进程
        int status;
        pid_t wait_ret = wait(&status);  // 等待子进程完成

        if (wait_ret > 0) {
            printf("父进程捕获到子进程 %d 结束，返回状态 %d。\n", wait_ret, WEXITSTATUS(status));
        } else {
            printf("父进程调用 wait() 失败。\n");
        }
        printf("父进程：子进程已创建\n");
        printf("父进程：子进程的PID是 %d\n", pid);
    }

    return 0;
}
