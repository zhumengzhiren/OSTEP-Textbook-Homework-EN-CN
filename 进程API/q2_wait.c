#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/file.h>
#include <sys/wait.h>  // 需要包含wait函数

int main() {
    int fd = open("q2_wait.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        printf("文件打开失败\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork失败\n");
        return 1;
    }

    if (pid == 0) {  // 子进程
        flock(fd, LOCK_EX);  // 获取文件写锁
        for (int i = 1; i <= 100; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "子进程写入: %d\n", i);
            write(fd, buffer, strlen(buffer));
        }
        flock(fd, LOCK_UN);  // 释放文件锁
    } else {  // 父进程
        wait(NULL);  // 等待子进程完成
        flock(fd, LOCK_EX);  // 获取文件写锁
        for (int i = 101; i <= 200; i++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "父进程写入: %d\n", i);
            write(fd, buffer, strlen(buffer));
        }
        flock(fd, LOCK_UN);  // 释放文件锁
    }

    close(fd);
    return 0;
}
