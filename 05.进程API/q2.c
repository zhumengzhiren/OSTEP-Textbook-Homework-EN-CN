#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // 使用open()打开文件，文件描述符返回
    int fd = open("q2.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd < 0) {
        printf("文件打开失败\n");
        return 1;
    }

    pid_t pid = fork();  // 创建子进程
    if (pid < 0) {  // fork()失败
        printf("Fork失败\n");
        return 1;
    }
    
    if (pid == 0) {  // 子进程
        for (int i = 1; i <= 100; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "子进程写入: %d\n", i);  // 格式化字符串
            write(fd, buffer, strlen(buffer));  // 写入子进程的信息
        }
    } else {  // 父进程
        for (int i = 101; i <= 200; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "父进程写入: %d\n", i);  // 格式化字符串
            write(fd, buffer, strlen(buffer));  // 写入父进程的信息
        }
    }

    close(fd);  // 关闭文件
    return 0;
}
