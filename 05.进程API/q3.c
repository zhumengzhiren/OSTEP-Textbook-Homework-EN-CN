#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];  // 创建一个管道
    if (pipe(pipefd) == -1) {
        printf("管道创建失败\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork失败\n");
        return 1;
    }

    if (pid == 0) {  // 子进程
        close(pipefd[0]);  // 关闭管道的读端
        printf("hello\n");
        write(pipefd[1], "done", 4);  // 向管道写入通知，告诉父进程可以继续
        close(pipefd[1]);  // 关闭写端
    } else {  // 父进程
        char buffer[5];
        close(pipefd[1]);  // 关闭管道的写端
        read(pipefd[0], buffer, 4);  // 阻塞等待子进程写入数据
        buffer[4] = '\0';  // 确保字符串结束
        if (strcmp(buffer, "done") == 0) {  // 收到子进程的通知
            printf("goodbye\n");
        }
        close(pipefd[0]);  // 关闭读端
    }

    return 0;
}
