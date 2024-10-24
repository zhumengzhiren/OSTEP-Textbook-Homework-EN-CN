概述
这个程序 scheduler.py 允许你查看不同调度算法在响应时间、周转时间和总等待时间等调度指标下的表现。程序中“实现”了三种调度器：FIFO、SJF 和 RR。

运行该程序分为两步。

首先，运行时不加 -c 参数：这样可以查看调度问题的描述，而不会直接给出答案。例如，如果你想使用 FIFO 策略计算三个作业的响应时间、周转时间和等待时间，可以运行以下命令：

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100
```

如果这不起作用，试试以下命令：

```sh
prompt> python ./scheduler.py -p FIFO -j 3 -s 100
```
这指定了使用 FIFO 策略，并且有 3 个作业，最重要的是，使用特定的随机种子 100。如果你想查看这个问题的解答，你需要再次指定相同的随机种子。让我们运行它并查看结果。你会看到以下输出：

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job: 
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)
```

现在计算每个作业的周转时间、响应时间和等待时间。完成后，可以再次运行此程序，使用相同的参数，但加上 -c 参数，这样就可以看到解答了。你可以使用 -s <某个数字> 或者自行指定作业列表（例如 -l 10,15,20）来生成不同的问题供你练习。

如上例所示，生成了三个作业：作业 0 长度为 1，作业 1 长度为 4，作业 2 长度为 7。程序现在提示你可以用这些数据计算一些统计值，看看你是否掌握了基本概念。

一旦你完成计算，可以使用相同的程序来“解答”问题，查看你是否正确。要做到这一点，使用 -c 参数。输出如下：

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100 -c
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job: 
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)

** Solutions **

Execution trace:
  [time   0] Run job 0 for 1.00 secs (DONE)
  [time   1] Run job 1 for 4.00 secs (DONE)
  [time   5] Run job 2 for 7.00 secs (DONE)

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 1.00  Wait 0.00
  Job   1 -- Response: 1.00  Turnaround 5.00  Wait 1.00
  Job   2 -- Response: 5.00  Turnaround 12.00  Wait 5.00

  Average -- Response: 2.00  Turnaround 6.00  Wait 2.00
```
如图所示，加上 -c 参数后可以看到具体的执行过程。作业 0 先运行了 1 秒，作业 1 接着运行了 4 秒，然后作业 2 运行了 7 秒。FIFO 策略非常简单，执行结果也很直观。执行轨迹显示了这些结果。

最终统计数据也很有用：它计算了“响应时间”（作业到达后等待首次运行的时间）、“周转时间”（从作业到达到完成的总时间）和总的“等待时间”（就绪但未运行的时间）。这些数据分别为每个作业计算并给出了平均值。当然，你应该在使用 -c 参数之前就自行计算这些数据！

如果你想尝试相同类型的问题，但使用不同的输入，可以更改作业的数量或随机种子。不同的随机种子为你生成了无限数量的不同问题，而 -c 参数可以用来检查你的答案。不断练习直到你完全理解这些概念。

另一个有用的参数是 -l（小写字母 L），它允许你指定要调度的具体作业。例如，如果你想查看 SJF 在 5、10 和 15 长度的三个作业下的表现，可以运行以下命令：

```sh
prompt> ./scheduler.py -p SJF -l 5,10,15
ARG policy SJF
ARG jlist 5,10,15

Here is the job list, with the run time of each job: 
  Job 0 (length = 5.0)
  Job 1 (length = 10.0)
  Job 2 (length = 15.0)
...
```
然后你可以使用 -c 参数查看解答。注意，当你指定具体的作业时，不需要指定随机种子或作业数量：作业长度是通过你逗号分隔的列表生成的。

当然，使用 SJF（最短作业优先）或 RR（轮转调度）策略时，情况会更有趣。试试看吧！

你也可以随时运行以下命令：

```sh
prompt> ./scheduler.py -h
```
来获取所有标志和选项的完整列表（包括设置 RR 调度器的时间片的选项）。