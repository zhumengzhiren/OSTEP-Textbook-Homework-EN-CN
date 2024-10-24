# 概览：`generator.py`

这个工具 `generator.py` 允许用户创建一些小的 C 程序，用于以不同方式调用 `fork`，以更好地理解 `fork` 的工作原理。

一个示例用法如下：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./generator.py -n 1 -s 0
</code></div></div></pre>

运行此命令时，您将看到一个随机生成的 C 程序。在这种情况下，您将看到类似于以下内容的输出：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>c</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-c">#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die() {
    int rc = wait(NULL);
    assert(rc > 0);
}

int fork_or_die() {
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[]) {
    // process a
    if (fork_or_die() == 0) {
        sleep(6);
        // process b
        exit(0);
    }
    wait_or_die();
    return 0;
}
</code></div></div></pre>

让我们稍微了解一下这段代码。代码的第一部分（从顶部到 `main()` 开始）将包含在每个生成的 C 程序中。代码的两个部分 `wait_or_die()` 和 `fork_or_die()` 只是对 `wait` 和 `fork` 系统调用的简单包装器，它们通常会成功（因为它们通常会成功），或者通过检查返回代码（存储在 `rc` 中）检测到错误，并通过 `assert()` 调用退出。这些包装器在仅在失败时简单地退出是可以接受的情况下很有用（在这里是可以接受的，但并非总是如此），并且使 `main()` 中的代码更易于阅读。

附注：`assert()`，如果您不熟悉，是一个简单检查传递给它的表达式的宏。如果断言为真，`assert()` 简单地返回并且程序继续执行。如果为假，则进程将退出。

代码的有趣部分（随着不同的随机种子而变化）在于 `main()` 中。在这里，我们看到主进程，我们将其称为“进程 a”（或简称为“a”），开始运行，调用 `fork_or_die()` 来创建另一个进程，然后等待该进程完成（通过调用 `wait_or_die()`）。

子进程（称为“b”）只是休眠一段时间（这里是4秒），然后退出。

然后，对您的挑战就是预测当此程序运行时输出将会是什么样子。通常，我们可以使用 `-c` 标志来获得结果：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./generator.py -n 1 -s 0 -c
  0 a+
  0 a->b
  6      b+
  6      b-
  6 a<-b
prompt> 
</code></div></div></pre>

阅读输出的方法如下。第一列显示某些事件发生的时间。在这种情况下，在时间0有两个事件发生。首先，进程 a 开始运行（用 `a+` 表示）；然后，a 调用 `fork` 并创建 b（用 `a->b` 表示）。

然后，b 开始运行，并立即休眠6秒，如代码中所示。一旦这个休眠完成，b 就会打印出它已经被创建了（`b+` 表示），但它并没有做太多事情；实际上，它只是退出，这也显示了（`b-`）。在输出中，这两者都被显示在时间6；然而，在实际中，我们知道 `b+` 发生在 `b-` 之前。

最后，一旦 b 已经退出，其父进程 a 中的 `wait_or_die()` 调用返回，然后进行最后的输出（`a<-b`）以表示这已经发生了。

有许多标志可以控制随机生成的代码的创建。它们是：

* `-s SEED` - 不同的随机种子会产生不同的程序
* `-n NUM_ACTIONS` - 程序应该包含多少个动作（`fork`，`wait`）
* `-f FORK_CHANCE` - `fork()` 将被添加的概率（1-99％）
* `-w WAIT_CHANCE` - 同上，但是 `wait()`（当然，必须有未完成的 `fork` 才能调用）
* `-e EXIT_CHANCE` - 进程将 `exit` 的概率
* `-S MAX_SLEEP_TIME` - 在代码中添加休眠时选择的最大休眠时间

还有一些控制为代码创建的 C 文件的标志：

* `-r READABLE` - 这是显示给您的文件（并针对可读性进行了优化）
* `-R RUNNABLE` - 这是将被编译和运行的文件；它与上述文件相同，但添加了打印语句等

最后，还有另一个标志 `-A`，它允许您精确指定程序。例如：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./generator.py -A "fork b,1 {} wait"
</code></div></div></pre>

生成的 C 代码：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>c</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-c">int main(int argc, char *argv[]) {
    // process a
    if (fork_or_die() == 0) {
        sleep(1);
        // process b
        exit(0);
    }
    wait_or_die();
    return 0;
}
</code></div></div></pre>

此命令创建默认进程（"a"），然后 "a" 创建 "b"，"b" 休眠 1 秒，然后不做任何其他事情；与此同时，"a" 然后等待 "b" 完成。

更复杂的示例也可以创建。例如：

* `-A "fork b,1 {} fork c,2 {} wait wait"` - 进程 "a" 创建两个进程 "b" 和 "c"，然后等待两者都完成
* `-A "fork b,1 {fork c,2 {} fork d,3 {} wait wait} wait"` - 进程 "a" 创建 "b"，然后等待其完成；"b" 创建 "c" 和 "d"，然后等待它们完成。

阅读并完成作业问题，以更全面地理解 `fork`。
