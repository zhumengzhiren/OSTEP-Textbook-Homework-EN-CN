# 概览

这个程序叫做 `process-run.py`，它允许你查看进程在 CPU 上运行时的状态如何变化。如本章所述，进程可以处于几种不同的状态：

```sh
RUNNING - 进程正在使用 CPU
READY   - 进程可以使用 CPU，但是（不幸的是）有其他进程在使用
BLOCKED - 进程正在等待 I/O 完成（例如，它向磁盘发出了请求）
DONE    - 进程已完成执行
```


在本作业中，我们将看到这些进程状态在程序运行时如何变化，从而更好地了解这些东西是如何工作的。

要运行程序并获取其选项，请执行以下操作：

```sh
prompt> ./process-run.py -h
```

如果这不起作用，请在命令之前键入 `python`，如下所示：

```sh
prompt> python process-run.py -h
```

你应该会看到如下内容：

```sh
Usage: process-run.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -l PROCESS_LIST, --processlist=PROCESS_LIST
                        a comma-separated list of processes to run, in the
                        form X1:Y1,X2:Y2,... where X is the number of
                        instructions that process should run, and Y the
                        chances (from 0 to 100) that an instruction will use
                        the CPU or issue an IO
  -L IO_LENGTH, --iolength=IO_LENGTH
                        how long an IO takes
  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO,
                        SWITCH_ON_END
  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER,
                        IO_RUN_IMMEDIATE
  -c                    compute answers for me
  -p, --printstats      print statistics at end; only useful with -c flag
                        (otherwise stats are not printed)
```

最重要的要理解的选项是 `PROCESS_LIST`（由 -l 或 --processlist 标志指定），它准确指定了每个运行的程序（或 '进程'）将要做什么。一个进程由指令组成，每个指令只能执行两件事之一：

* 使用 CPU
* 发出一个 I/O（并等待其完成）

当一个进程使用 CPU（而没有进行任何 I/O）时，它应该简单地在在 RUNNING 状态和 READY 状态之间交替。例如，下面是一个简单的运行，只有一个程序正在运行，并且该程序仅使用 CPU（不执行任何 I/O）。

```sh
prompt> ./process-run.py -l 5:100 
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)

prompt> 
```


在这里，我们指定的进程是 "5:100"，这意味着它应该包含 5 条指令，每个指令是 CPU 指令的概率为 100%。

你可以通过使用 -c 标志查看进程的运行情况，该标志会为你计算答案：

```sh
prompt> ./process-run.py -l 5:100 -c
Time     PID: 0        CPU        IOs
  1     RUN:cpu          1
  2     RUN:cpu          1
  3     RUN:cpu          1
  4     RUN:cpu          1
  5     RUN:cpu          1
```

这个结果并不太有趣：该进程在整个运行过程中一直使用 CPU，并且在此期间保持 CPU 繁忙，不执行任何 I/O。

让我们稍微复杂一点，运行两个进程：

```sh
prompt> ./process-run.py -l 5:100,5:100
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  Scheduler will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

在这种情况下，运行两个不同的进程，每个进程再次只是使用 CPU。当操作系统运行它们时会发生什么？我们来看看：

```sh
prompt> ./process-run.py -l 5:100,5:100 -c
Time     PID: 0     PID: 1        CPU        IOs
  1     RUN:cpu      READY          1
  2     RUN:cpu      READY          1
  3     RUN:cpu      READY          1
  4     RUN:cpu      READY          1
  5     RUN:cpu      READY          1
  6        DONE    RUN:cpu          1
  7        DONE    RUN:cpu          1
  8        DONE    RUN:cpu          1
  9        DONE    RUN:cpu          1
 10        DONE    RUN:cpu          1
```

如上所示，首先 PID 为 0 的进程运行，而进程 1 准备运行，但只有等到 0 完成时才会运行。当 0 完成时，它移至 DONE 状态，而 1 运行。当 1 完成时，跟踪就结束了。

让我们再看一个例子，其中进程只发出 I/O 请求。在此处，我们指定 I/O 的持续时间为 5 个时间单位，使用 -L 标志。

```sh
prompt> ./process-run.py -l 3:0 -L 5
Produce a trace of what would happen when you run these processes:
Process 0
  io
  io_done
  io
  io_done
  io
  io_done

Important behaviors:
  System will switch when the current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO will run LATER (when it is its turn)
```

你认为执行跟踪会是什么样子呢？让我们来看看：

```sh
prompt> ./process-run.py -l 3:0 -L 5 -c
Time    PID: 0       CPU       IOs
  1         RUN:io             1
  2        BLOCKED                           1
  3        BLOCKED                           1
  4        BLOCKED                           1
  5        BLOCKED                           1
  6        BLOCKED                           1
  7*   RUN:io_done             1
  8         RUN:io             1
  9        BLOCKED                           1
 10        BLOCKED                           1
 11        BLOCKED                           1
 12        BLOCKED                           1
 13        BLOCKED                           1
 14*   RUN:io_done             1
 15         RUN:io             1
 16        BLOCKED                           1
 17        BLOCKED                           1
 18        BLOCKED                           1
 19        BLOCKED                           1
 20        BLOCKED                           1
 21*   RUN:io_done             1
```


正如你所看到的，程序只是发出了三个 I/O。当发出每个 I/O 时，进程移至 BLOCKED 状态，而在设备正在为 I/O 提供服务时，CPU 处于空闲状态。

为了处理 I/O 的完成，还有一个 CPU 操作。请注意，处理 I/O 启动和完成的单个指令并不特别现实，但在这里只是为了简单起见。

让我们打印一些统计信息（运行与上述相同的命令，但使用 -p 标志）以查看一些总体行为：

```sh
Stats: Total Time 21
Stats: CPU Busy 6 (28.57%)
Stats: IO Busy  15 (71.43%)
```

正如你所看到的，跟踪花费了 21 个时钟滴答的时间，但 CPU 忙碌的时间不到 30%。另一方面，I/O 设备非常忙碌。通常情况下，我们希望保持所有设备忙碌，因为这是资源更好的利用。

还有一些其他重要的标志：

```sh
  -s SEED, --seed=SEED  the random seed  
    this gives you way to create a bunch of different jobs randomly

  -L IO_LENGTH, --iolength=IO_LENGTH
    this determines how long IOs take to complete (default is 5 ticks)

  -S PROCESS_SWITCH_BEHAVIOR, --switch=PROCESS_SWITCH_BEHAVIOR
                        when to switch between processes: SWITCH_ON_IO, SWITCH_ON_END
    this determines when we switch to another process:
    - SWITCH_ON_IO, the system will switch when a process issues an IO
    - SWITCH_ON_END, the system will only switch when the current process is done 

  -I IO_DONE_BEHAVIOR, --iodone=IO_DONE_BEHAVIOR
                        type of behavior when IO ends: IO_RUN_LATER, IO_RUN_IMMEDIATE
    this determines when a process runs after it issues an IO:
    - IO_RUN_IMMEDIATE: switch to this process right now
    - IO_RUN_LATER: switch to this process when it is natural to 
      (e.g., depending on process-switching behavior)
```

现在，去回答本章末尾的问题，以获取更多信息。
