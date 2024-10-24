# 概述：`fork.py`

模拟器 `fork.py` 是一个简单的工具，用于展示在创建和销毁进程时进程树的样子。

要运行它，只需：
```sh
prompt> ./fork.py
```

然后，您将看到一系列操作，例如是否一个进程调用 `fork` 来创建另一个进程，或者是否一个进程调用 `exit` 来停止运行。

每个正在运行的进程都可以有多个子进程（或没有）。每个进程，除了初始进程（在这里简称为 `a`），都有一个父进程。因此，所有进程都在一个树中相关联，以初始进程为根。我们将这个树称为 `进程树`，理解进程创建和销毁时它的样子是这个简单作业的目的。

# 简单示例

这里是一个简单的例子：

```sh
prompt> ./fork.py -s 4

                           Process Tree:
                               a
Action: a forks b
Process Tree?
Action: a forks c
Process Tree?
Action: b forks d
Process Tree?
Action: d EXITS
Process Tree?
Action: a forks e
Process Tree?
```

从输出中，您可以看到两件事。首先，在右侧是系统的初始状态。正如您所看到的，它包含一个名为 `a` 的进程。操作系统通常创建一个或几个初始进程来启动系统；例如，在Unix上，初始进程称为 `init`，它会在系统运行时生成其他进程。

其次，在左侧，您可以看到一系列的 `Action` 列表，其中发生各种操作，然后提出一个关于进程树状态的问题。

要解决并显示所有输出，请使用 `-c` 标志，如下所示：

```sh
prompt> ./fork.py -s 4 -c                                                                       +100

                           Process Tree:
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
```

正如您所看到的，现在显示了由特定操作产生的预期树（从左到右显示）。在第一个操作“a forks b”之后，您会看到一个非常简单的树，其中 `a` 被显示为 `b` 的父级。经过一些分支后，`d` 调用 `exit`，这减少了树。最后，创建了 `e`，并且最终树以 `a` 为 `b`、`c` 和 `e`（被视为“兄弟”）的父亲而结束。

在简化模式下，您可以通过使用 `-F` 标志来测试自己，尝试写下最终的进程树：

```sh
prompt> ./fork.py -s 4 -F
                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: b forks d
Action: d EXITS
Action: a forks e

                        Final Process Tree?
```

再次，您可以使用 `-c` 标志来计算答案，看看自己是否正确（在这种情况下，您应该是正确的，因为这是相同的问题！）

# 其他选项

`fork` 模拟器还有许多其他选项。

您可以使用 `-t` 标志将问题反过来，允许您查看进程树状态，然后猜测可能发生了什么操作。

您可以使用不同的随机种子（`-s` 标志）或者不指定随机种子以获得不同的随机生成序列。

您可以使用 `-f` 标志更改分支操作的百分比与退出相比）。

您可以使用 `-A` 标志指定特定的分支和退出序列。例如，要使 `a` 分支 `b`，`b` 然后分支 `c`；`c` 退出，最后，`a` 分支 `d`，只需键入（我们在这里显示 `-c` 以解决问题）：

```sh
prompt> ./fork.py -A a+b,b+c,c-,a+d -c

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
```

您只能使用 `-F` 标志显示最终输出（然后查看是否能猜到所有的中间步骤）。

最后，您可以使用 `-P` 标志更改树的打印样式。
