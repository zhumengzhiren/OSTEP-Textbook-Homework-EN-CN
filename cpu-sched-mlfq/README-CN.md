这个程序 `mlfq.py` 允许你观察在本章中介绍的 MLFQ 调度器的行为。与之前一样，你可以使用它生成带有不同随机种子的问题，或者使用它构建一个精心设计的实验，以查看在不同情况下 MLFQ 如何工作。要运行该程序，请键入：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./mlfq.py
</code></div></div></pre>

使用帮助标志 (-h) 来查看选项

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">Usage: mlfq.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -n NUMQUEUES, --numQueues=NUMQUEUES
                        number of queues in MLFQ (if not using -Q)
  -q QUANTUM, --quantum=QUANTUM
                        length of time slice (if not using -Q)
  -a ALLOTMENT, --allotment=ALLOTMENT
                        length of allotment (if not using -A)
  -Q QUANTUMLIST, --quantumList=QUANTUMLIST
                        length of time slice per queue level, specified as
                        x,y,z,... where x is the quantum length for the
                        highest priority queue, y the next highest, and so
                        forth
  -A ALLOTMENTLIST, --allotmentList=ALLOTMENTLIST
                        length of time allotment per queue level, specified as
                        x,y,z,... where x is the # of time slices for the
                        highest priority queue, y the next highest, and so
                        forth
  -j NUMJOBS, --numJobs=NUMJOBS
                        number of jobs in the system
  -m MAXLEN, --maxlen=MAXLEN
                        max run-time of a job (if randomly generating)
  -M MAXIO, --maxio=MAXIO
                        max I/O frequency of a job (if randomly generating)
  -B BOOST, --boost=BOOST
                        how often to boost the priority of all jobs back to
                        high priority
  -i IOTIME, --iotime=IOTIME
                        how long an I/O should last (fixed constant)
  -S, --stay            reset and stay at same priority level when issuing I/O
  -I, --iobump          if specified, jobs that finished I/O move immediately
                        to front of current queue
  -l JLIST, --jlist=JLIST
                        a comma-separated list of jobs to run, in the form
                        x1,y1,z1:x2,y2,z2:... where x is start time, y is run
                        time, and z is how often the job issues an I/O request
  -c                    compute answers for me
</code></div></div></pre>

有几种不同的方式可以使用模拟器。其中一种方式是生成一些随机作业，并尝试弄清它们在给定 MLFQ 调度器下的行为。例如，如果你想创建一个随机生成的包含三个作业的工作负载，只需输入：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./mlfq.py -j 3
</code></div></div></pre>

然后，你将看到具体的问题定义：


<pre><div class="bg-black rounded-md"><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">以下是输入列表：
OPTIONS jobs 3
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


对于每个作业，给出了三个定义特征：
  startTime：作业进入系统的时间
  runTime：作业完成所需的总CPU时间
  ioFreq：每 ioFreq 时间单位，作业发出一个I/O
          （I/O花费 ioTime 单位的时间来完成）

作业列表：
  Job  0: startTime   0 - runTime  84 - ioFreq   7
  Job  1: startTime   0 - runTime  42 - ioFreq   3
  Job  2: startTime   0 - runTime  51 - ioFreq   4

计算给定工作负载的执行跟踪。
如果愿意，还可以计算每个作业的响应时间和周转时间。

在完成时使用 -c 标志获取确切的结果时，你将看到以下内容：

```sh
执行跟踪：

[ time 0 ] JOB BEGINS 由 JOB 0
[ time 0 ] JOB BEGINS 由 JOB 1
[ time 0 ] JOB BEGINS 由 JOB 2
[ time 0 ] 在优先级 2 下运行 JOB 0 [ TICKS 9 ALLOT 1 TIME 83 (of 84) ]
[ time 1 ] 在优先级 2 下运行 JOB 0 [ TICKS 8 ALLOT 1 TIME 82 (of 84) ]
[ time 2 ] 在优先级 2 下运行 JOB 0 [ TICKS 7 ALLOT 1 TIME 81 (of 84) ]
[ time 3 ] 在优先级 2 下运行 JOB 0 [ TICKS 6 ALLOT 1 TIME 80 (of 84) ]
[ time 4 ] 在优先级 2 下运行 JOB 0 [ TICKS 5 ALLOT 1 TIME 79 (of 84) ]
[ time 5 ] 在优先级 2 下运行 JOB 0 [ TICKS 4 ALLOT 1 TIME 78 (of 84) ]
[ time 6 ] 在优先级 2 下运行 JOB 0 [ TICKS 3 ALLOT 1 TIME 77 (of 84) ]
[ time 7 ] 由 JOB 0 发出 IO_START
I/O 完成
[ time 7 ] 在优先级 2 下运行 JOB 1 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
[ time 8 ] 在优先级 2 下运行 JOB 1 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
[ time 9 ] 在优先级 2 下运行 JOB 1 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
...

最终统计：
  Job  0: startTime   0 - response   0 - turnaround 175
  Job  1: startTime   0 - response   7 - turnaround 191
  Job  2: startTime   0 - response   9 - turnaround 168

  Avg  2: startTime n/a - response 5.33 - turnaround 178.00
</code></div></div></pre>

该跟踪以毫秒为单位，准确显示了调度器的决策。在此示例中，它首先运行作业 0 7 毫秒，直到作业 0 发出 I/O；这是完全可预测的，因为作业 0 的 I/O 频率设置为 7 毫秒，这意味着每运行 7 毫秒，它将发出一个 I/O 并等待其完成，然后继续。在这一点上，调度器切换到作业 1，在发出 I/O 之前仅运行 2 毫秒。调度器以这种方式打印整个执行跟踪，并最终计算每个作业的响应时间和周转时间，以及平均值。


您还可以控制模拟的各个方面。例如，您可以指定系统中希望有多少个队列（-n），以及这些队列的量子长度应该是多少（-q）；如果您想要更多的控制并为每个队列指定不同的量子长度，您还可以使用 -Q 指定每个队列的量子（时间片）长度，例如，-Q 10,20,30 模拟一个具有三个队列的调度器，最高优先级队列的时间片为 10 毫秒，次高优先级为 20 毫秒，低优先级队列为 30 毫秒。

您还可以单独控制每个队列的时间分配。这可以通过 -a 设置所有队列的时间分配，或通过 -A 设置每个队列的时间分配，例如，-A 20,40,60 将每个队列的时间分配分别设置为 20 毫秒、40 毫秒和 60 毫秒。请注意，虽然章节中讨论的分配是以时间为单位的，但在这里是以时间片数量为单位的，即，如果给定队列的时间片长度为 10 毫秒，而分配为 2，则作业在该队列级别上可以运行 2 个时间片（20 毫秒）之后再降低优先级。

如果您正在随机生成作业，还可以控制它们可能运行的时间（-m）或它们生成 I/O 的频率（-M）。但如果您想对运行在系统中的作业的确切特性有更多控制，可以使用 -l（小写字母 L）或 --jlist，它允许您指定要模拟的作业集的确切形式：x1,y1,z1:x2,y2,z2:...，其中 x 是作业的开始时间，y 是运行时间（即，需要多少 CPU 时间），z 是 I/O 频率（即，运行 z 毫秒后，作业发出一个 I/O；如果 z 为 0，则不发出 I/O）。

例如，如果您想要重现图 8.3 中的示例，则可以按以下方式指定作业列表：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./mlfq.py --jlist 0,180,0:100,20,0 -q 10
</code></div></div></pre>

以这种方式运行模拟器会创建一个三级 MLFQ，每个级别都有一个 10 毫秒的时间片。创建了两个作业：作业 0 从时间 0 开始，总共运行了 180 毫秒，并且从不发出 I/O；作业 1 从 100 毫秒开始，只需 20 毫秒的 CPU 时间即可完成，并且也从不发出 I/O。

最后，还有三个感兴趣的参数。-B 标志，如果设置为非零值，会将所有作业提升到最高优先级队列，每隔 N 毫秒执行一次，如下所示：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./mlfq.py -B N
</code></div></div></pre>

调度器使用此功能来避免饥饿，如章节中所讨论的那样。但默认情况下，它是关闭的。

-S 标志调用旧的规则 4a 和 4b，这意味着如果作业在完成其时间片之前发出 I/O，它将在恢复执行时返回到相同的优先级队列，并且其完整的分配保持不变。这使得对调度器进行调优成为可能。

最后，您还可以通过使用 -i 标志轻松更改 I/O 的持续时间。在这个简化的模型中，默认情况下，每个 I/O 需要固定的时间，为 5 毫秒，或者您可以使用此标志进行设置。

您还可以尝试一下，看看是否将刚刚完成 I/O 的作业移到其所在队列的队首还是队尾，使用 -I 标志。试试看，这很有趣！
