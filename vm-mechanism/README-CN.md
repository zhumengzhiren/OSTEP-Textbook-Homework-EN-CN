此程序允许您查看带有基址和界限寄存器的系统中如何执行地址转换。与以前一样，运行程序有两个步骤，以测试您对基址和界限的理解。首先，不使用 -c 标志运行以生成一组转换，并查看您是否可以正确执行地址转换。然后，在完成后，使用 -c 标志运行以检查您的答案。

在这个作业中，我们将假设一个略有不同的地址空间，而不是我们通常的堆栈和堆位于空间两端的典型情况。相反，我们将假设地址空间有一个代码段，然后是一个固定大小的（较小的）堆栈，堆在其后以向下增长的方式，如下图所示。在这种配置中，只有一种增长方向，朝着地址空间的较高区域增长。

<pre><div class="dark bg-gray-950 rounded-md"><div class="flex items-center relative text-token-text-secondary bg-token-main-surface-secondary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">  -------------- 0KB
  |    Code    |
  -------------- 2KB
  |   Stack    |
  -------------- 4KB
  |    Heap    |
  |     |      |
  |     v      |
  -------------- 7KB
  |   (free)   |
  |     ...    |
</code></div></div></pre>

在图中，界限寄存器将被设置为 7KB，因为它代表地址空间的结尾。对界限内任何地址的引用都将被视为合法；超出此值的引用是越界的，因此硬件会引发异常。

要使用默认标志运行，请在命令行中键入 `relocation.py`。结果应该类似于以下内容：

<pre><div class="dark bg-gray-950 rounded-md"><div class="flex items-center relative text-token-text-secondary bg-token-main-surface-secondary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./relocation.py 
...
基址和界限寄存器信息：

  基址   : 0x00003082 (十进制 12418)
  界限  : 472

虚拟地址跟踪
  VA  0: 0x01ae (十进制:430) -> 物理地址或违规？
  VA  1: 0x0109 (十进制:265) -> 物理地址或违规？
  VA  2: 0x020b (十进制:523) -> 物理地址或违规？
  VA  3: 0x019e (十进制:414) -> 物理地址或违规？
  VA  4: 0x0322 (十进制:802) -> 物理地址或违规？
</code></div></div></pre>

对于每个虚拟地址，要么写下它转换为的物理地址，要么写下它是越界地址（段错误）。对于此问题，您应该假设有一个给定大小的简单虚拟地址空间。

正如您所见，作业只是生成随机的虚拟地址。对于每个虚拟地址，您都应确定它是否在范围内，如果在范围内，则确定它转换为哪个物理地址。使用 `-c`（“为我计算这个”标志）运行将为我们提供这些转换的结果，即它们是否有效，如果有效，则是生成的物理地址。为方便起见，所有数字均以十六进制和十进制给出。

<pre><div class="dark bg-gray-950 rounded-md"><div class="flex items-center relative text-token-text-secondary bg-token-main-surface-secondary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./relocation.py -c
...
虚拟地址跟踪
  VA  0: 0x01ae (十进制:430) -> 有效: 0x00003230 (十进制:12848)
  VA  1: 0x0109 (十进制:265) -> 有效: 0x0000318b (十进制:12683)
  VA  2: 0x020b (十进制:523) -> 段错误
  VA  3: 0x019e (十进制:414) -> 有效: 0x00003220 (十进制:12832)
  VA  4: 0x0322 (十进制:802) -> 段错误
</code></div></div></pre>

具有基址 12418（十进制）的地址，地址 430 在范围内（即它小于 472 的界限寄存器），因此转换为 430 加上 12418 或 12848。如上所示，一些地址是越界的（523、802），因为它们超出了界限。相当简单，不是吗？确实，这就是基址和界限的美妙之处：它是如此简单！

您可以使用一些标志来更好地控制正在进行的操作：

<pre><div class="dark bg-gray-950 rounded-md"><div class="flex items-center relative text-token-text-secondary bg-token-main-surface-secondary px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>sh</span><span class="" data-state="closed"><button class="flex gap-1 items-center"><svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" class="icon-sm"><path fill-rule="evenodd" clip-rule="evenodd" d="M12 4C10.8954 4 10 4.89543 10 6H14C14 4.89543 13.1046 4 12 4ZM8.53513 4C9.22675 2.8044 10.5194 2 12 2C13.4806 2 14.7733 2.8044 15.4649 4H17C18.6569 4 20 5.34315 20 7V19C20 20.6569 18.6569 22 17 22H7C5.34315 22 4 20.6569 4 19V7C4 5.34315 5.34315 4 7 4H8.53513ZM8 6H7C6.44772 6 6 6.44772 6 7V19C6 19.5523 6.44772 20 7 20H17C17.5523 20 18 19.5523 18 19V7C18 6.44772 17.5523 6 17 6H16C16 7.10457 15.1046 8 14 8H10C8.89543 8 8 7.10457 8 6Z" fill="currentColor"></path></svg>Copy code</button></span></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-sh">prompt> ./relocation.py -h
用法: relocation.py [选项]

选项:
  -h, --help            显示此帮助信息并退出
  -s SEED, --seed=SEED  随机种子
  -a ASIZE, --asize=ASIZE 地址空间大小（例如，16，64k，32m）
  -p PSIZE, --physmem=PSIZE 物理内存大小（例如，16，64k）
  -n NUM, --addresses=NUM 要生成的虚拟地址数
  -b BASE, --b=BASE     基址寄存器的值
  -l LIMIT, --l=LIMIT   限制寄存器的值
  -c, --compute         为我计算答案
</code></div></div></pre>

特别是，您可以控制虚拟地址空间大小（-a）、物理内存大小（-p）、要生成的虚拟地址数（-n）以及此进程的基址和界限寄存器的值（分别为 -b 和 -l）。
