# 概述：`fork.py`

模拟器 `fork.py` 是一个简单的工具，用于展示在创建和销毁进程时进程树的样子。

要运行它，只需：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./fork.py
</code></div></div></pre>

然后，您将看到一系列操作，例如是否一个进程调用 `fork` 来创建另一个进程，或者是否一个进程调用 `exit` 来停止运行。

每个正在运行的进程都可以有多个子进程（或没有）。每个进程，除了初始进程（在这里简称为 `a`），都有一个父进程。因此，所有进程都在一个树中相关联，以初始进程为根。我们将这个树称为 `进程树`，理解进程创建和销毁时它的样子是这个简单作业的目的。

# 简单示例

这里是一个简单的例子：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./fork.py -s 4

                           进程树:
                               a
Action: a forks b
进程树？
Action: a forks c
进程树？
Action: b forks d
进程树？
Action: d EXITS
进程树？
Action: a forks e
进程树？
</code></div></div></pre>

从输出中，您可以看到两件事。首先，在右侧是系统的初始状态。正如您所看到的，它包含一个名为 `a` 的进程。操作系统通常创建一个或几个初始进程来启动系统；例如，在Unix上，初始进程称为 `init`，它会在系统运行时生成其他进程。

其次，在左侧，您可以看到一系列的 `Action` 列表，其中发生各种操作，然后提出一个关于进程树状态的问题。

要解决并显示所有输出，请使用 `-c` 标志，如下所示：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./fork.py -s 4 -c                                                                       +100

                           进程树:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: b forks d
                               a
                               ├── b
                               │   └── d
                               └── c
Action: d EXITS
                               a
                               ├── b
                               └── c
Action: a forks e
                               a
                               ├── b
                               ├── c
                               └── e
prompt>
</code></div></div></pre>

正如您所看到的，现在显示了由特定操作产生的预期树（从左到右显示）。在第一个操作“a forks b”之后，您会看到一个非常简单的树，其中 `a` 被显示为 `b` 的父级。经过一些分支后，`d` 调用 `exit`，这减少了树。最后，创建了 `e`，并且最终树以 `a` 为 `b`、`c` 和 `e`（被视为“兄弟”）的父亲而结束。

在简化模式下，您可以通过使用 `-F` 标志来测试自己，尝试写下最终的进程树：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./fork.py -s 4 -F
                           进程树:
                               a

Action: a forks b
Action: a forks c
Action: b forks d
Action: d EXITS
Action: a forks e

                        最终进程树?
</code></div></div></pre>

再次，您可以使用 `-c` 标志来计算答案，看看自己是否正确（在这种情况下，您应该是正确的，因为这是相同的问题！）

# 其他选项

`fork` 模拟器还有许多其他选项。

您可以使用 `-t` 标志将问题反过来，允许您查看进程树状态，然后猜测可能发生了什么操作。

您可以使用不同的随机种子（`-s` 标志）或者不指定随机种子以获得不同的随机生成序列。

您可以使用 `-f` 标志更改分支操作的百分比
