#include <stdio.h>
#include <unistd.h>  // for fork()

int main() {
    int x = 100;  // 主进程中的变量x

    pid_t pid = fork();  // 创建子进程

    if (pid < 0) {  // fork() 失败
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {  // 子进程
        printf("子进程：初始x = %d\n", x);
        x = 200;  // 修改子进程中的x
        printf("子进程：修改后的x = %d\n", x);
    } else {  // 父进程
        printf("父进程：初始x = %d\n", x);
        x = 300;  // 修改父进程中的x
        printf("父进程：修改后的x = %d\n", x);
    }

    printf("x = %d, pid = %d\n", x, pid);  // 打印主进程中的x

    return 0;
}
