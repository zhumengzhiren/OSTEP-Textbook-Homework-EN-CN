#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // fork() 失败
        printf("fork() failed!\n");
        return 1;
    } else if (pid == 0) {
        // 子进程，尝试 exec 系列变种
        // 1. 使用 execl()
        // execl("/bin/ls", "ls", "-l", NULL);

        // 2. 使用 execle()
        // char *envp[] = { "HOME=/usr/home", "LOGNAME=home", NULL };
        // execle("/bin/ls", "ls", "-l", NULL, envp);

        // 3. 使用 execlp()
        // execlp("ls", "ls", "-l", NULL);

        // 4. 使用 execv()
        // char *args[] = { "ls", "-l", NULL };
        // execv("/bin/ls", args);

        // 5. 使用 execvp()
        // char *args[] = { "ls", "-l", NULL };
        // execvp("ls", args);

        // 6. 使用 execvP()
        // char *args[] = { "ls", "-l", NULL };
        // execvP("ls", "/bin", args);

        // 如果 exec 执行失败，打印错误并退出
        perror("exec failed");
        exit(1);
    } else {
        // 父进程，等待子进程结束
        wait(NULL);
        printf("Child process finished\n");
    }

    return 0;
}
