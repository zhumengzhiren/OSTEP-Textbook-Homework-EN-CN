这个程序是 lottery.py，它允许您查看抽彩调度器的工作原理。与往常一样，运行程序有两个步骤。首先，不使用 -c 标志运行：这会显示您需要解决的问题，而不会显示答案。

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./lottery.py -j 2 -s 0
...
以下是作业列表，以及每个作业的运行时间：
  作业 0（长度 = 8，彩票 = 75）
  作业 1（长度 = 4，彩票 = 25）

以下是您将需要的一组随机数（最多）：
随机 511275
随机 404934
随机 783799
随机 303313
随机 476597
随机 583382
随机 908113
随机 504687
随机 281838
随机 755804
随机 618369
随机 250506
</code></div></div></pre>

以这种方式运行模拟器时，首先分配给您一些随机作业（这里长度分别为 8 和 4），每个作业都有一定数量的彩票（这里分别为 75 和 25）。模拟器还会提供一组随机数，您需要使用这些数来确定抽彩调度器将执行的操作。随机数被选择为介于 0 和一个大数之间；因此，您将不得不使用模运算符来计算中奖者（即，中奖者应该等于此随机数对系统中总彩票数取模的结果）。

使用 -c 运行将显示确切的计算结果：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./lottery.py -j 2 -s 0 -c
...
** 解决方案 **
随机 511275 -> 中奖彩票 75（共 100 张）-> 运行 1
  作业：  （  作业：0 剩余时间：8 彩票：75  ）  (*  作业：1 剩余时间：4 彩票：25  )
随机 404934 -> 中奖彩票 34（共 100 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：8 彩票：75  ）  （  作业：1 剩余时间：3 彩票：25  )
随机 783799 -> 中奖彩票 99（共 100 张）-> 运行 1
  作业：  （  作业：0 剩余时间：7 彩票：75  ）  (*  作业：1 剩余时间：3 彩票：25  )
随机 303313 -> 中奖彩票 13（共 100 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：7 彩票：75  ）  （  作业：1 剩余时间：2 彩票：25  )
随机 476597 -> 中奖彩票 97（共 100 张）-> 运行 1
  作业：  （  作业：0 剩余时间：6 彩票：75  ）  (*  作业：1 剩余时间：2 彩票：25  )
随机 583382 -> 中奖彩票 82（共 100 张）-> 运行 1
  作业：  （  作业：0 剩余时间：6 彩票：75  ）  (*  作业：1 剩余时间：1 彩票：25  )
--> 作业 1 在时间 6 完成
随机 908113 -> 中奖彩票 13（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：6 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
随机 504687 -> 中奖彩票 12（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：5 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
随机 281838 -> 中奖彩票 63（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：4 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
随机 755804 -> 中奖彩票 29（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：3 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
随机 618369 -> 中奖彩票 69（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：2 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
随机 250506 -> 中奖彩票 6（共 75 张）-> 运行 0
  作业：  （ *  作业：0 剩余时间：1 彩票：75  ）  （  作业：1 剩余时间：0 彩票：--- ）
--> 作业 0 在时间 12 完成</code></div></div></pre>


正如您从这个跟踪中所看到的，您需要做的是使用随机数来确定哪张彩票是中奖者。然后，根据中奖票，找出应该运行哪个作业。重复这个过程，直到所有作业都完成运行。就是这么简单 - 您只是手动模拟了彩票调度器的操作！

为了使这一点绝对清晰，让我们看一下上面示例中所做的第一个决定。在此时，我们有两个作业（作业 0 其运行时间为 8，有 75 张彩票；作业 1 其运行时间为 4，有 25 张彩票）。我们收到的第一个随机数是 511275。由于系统中有 100 张彩票，511275 % 100 等于 75，因此 75 就是我们的中奖彩票。

如果彩票 75 是赢家，我们只需在作业列表中搜索，直到找到它。第一个条目，对于作业 0，有 75 张票（从 0 到 74），因此没有中奖；下一个条目是作业 1，因此我们找到了我们的赢家，因此我们运行作业 1，运行时间为时间片长度（在此示例中为 1）。所有这些都显示在打印输出中，如下所示：

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">Random 511275 -> 中奖彩票 75（共 100 张）-> 运行 1
  作业：  （  作业：0 剩余时间：8 彩票：75  ）  (*  作业：1 剩余时间：4 彩票：25  )
</code></div></div></pre>

正如您所见，第一行总结了发生的情况，第二行简单地显示了整个作业队列，其中 * 表示选择的作业。

模拟器还有一些其他选项，其中大多数应该是不言自明的。尤其要注意的是，-l/--jlist 标志可用于指定一个确切的作业集以及它们的彩票值，而不总是使用随机生成的作业列表。

<pre><div class="bg-black rounded-md"><div class="flex items-center relative text-gray-200 bg-gray-800 dark:bg-token-surface-primary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./lottery.py -h
Usage: lottery.py [options]

Options:
  -h, --help      
      show this help message and exit
  -s SEED, --seed=SEED  
      the random seed
  -j JOBS, --jobs=JOBS  
      number of jobs in the system
  -l JLIST, --jlist=JLIST
      instead of random jobs, provide a comma-separated list
      of run times and ticket values (e.g., 10:100,20:100
      would have two jobs with run-times of 10 and 20, each
      with 100 tickets)
  -m MAXLEN, --maxlen=MAXLEN
      max length of job
  -T MAXTICKET, --maxtick=MAXTICKET
      maximum ticket value, if randomly assigned
  -q QUANTUM, --quantum=QUANTUM
      length of time slice
  -c, --compute
      compute answers for me</code></div></div></pre>
