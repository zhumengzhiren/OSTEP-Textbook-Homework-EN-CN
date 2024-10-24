#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pipefd[2];  // 管道的文件描述符数组 pipefd[0] 是读端，pipefd[1] 是写端

    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // 创建第一个子进程
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {  // 子进程1
        // 重定向标准输出到管道的写端
        dup2(pipefd[1], STDOUT_FILENO);
        // 关闭管道的读端，子进程1不需要读
        close(pipefd[0]);
        
        // 执行 ls 命令
        printf("ls -l");
        execlp("ls", "ls", NULL);
        
        close(pipefd[1]);
        exit(1);
    }

    // 创建第二个子进程
    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {  // 子进程2
        // 重定向标准输入到管道的读端
        dup2(pipefd[0], STDIN_FILENO);
        // 关闭管道的写端，子进程2不需要写
        close(pipefd[1]);
        // 执行 wc -l 命令
        
        execlp("wc", "wc", "-l", NULL);
        
        
        close(pipefd[0]);
        exit(1);
    }

    // 父进程
    // 父进程不需要使用管道的读写端，关闭它们
    close(pipefd[0]);
    close(pipefd[1]);
    
    // 等待两个子进程结束
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
