
1、Linux操作系统下各路径存放什么文件？（usr/dev/opt/etc/home/bin/media）

`/usr`: 各类软件 库. 可以把它当成一个软件园. 
`/dev`: 各类设备(device). 鼠标 键盘 终端等
`/opt`: 第三方软件集中管理的地方. `/lib` `/bin`等文件放在同一个目录下, 方便后续统一的移除
`etc`: 系统的各类配置文件存放位置, 目前接触到的`/etc/profile` 
`/home`: 各个用户的家目录, 存放用户的文件 数据 以及配置
`/bin`: 系统级别的各类可执行程序存放位置. 我们常用的终端命令就放在这里
`media`: 媒介文件夹, 就是U盘 SD卡 移动硬盘存放的位置


2、Linux 操作指令：
- 查看文件前5行
- 查看文件后5行 且实时查看
- 搜索文件是否包含特定内容
- 压缩与解压文件
- 创建软连接与硬链接
- 如何修改某网卡的ip地址
`head -n 5 main.c`
`tail -n 5 -f main.c`
`grep "hello" main.c`
`tar -zcvf main.tar.gz main.c hello.c`
`tar -zxvf main.tar.gz`
`ln src.c target.c`
`ln -s src.c target.c`
`nmcli connecttion show`
`nmcli connection modify ssh_ip ipv4.addresses 192.168.44.100/24 ipv4.gateway 192.168.44.1 ipv4.dns 8.8.8.8 ipv4.method manual`
或者图形界面的操作来设置.

3、软连接与硬链接的区别
区别: inode. 硬链接共享一个inode, 内容共享, 删除一个文件, 另一个文件访问也可以正常展示.不能跨系统访问, 也不能链接目录.
软链接, 各自都有自己的inode, 如果源文件被删, 就断链了. 可以跨系统, 也可以链接目录.

4、环境变量有什么用？什么时候需要使用到环境变量？如何配置环境变量？
给当前运行环境以及其子环境一些通用的配置信息, 以键值对的方式存储.
比如用到动态库 系统级别的命令 当前文件路径 当前用户等等.
通过export 关键字.还有一些配置文件. 用户级: ~/.bashrc 系统级 /etc/profile

5、现有文件main.c 1.c 1.h 2.c 2.h 五个文件，编写一个Makefile将五个文件编译成main.exe  
要求使用符号优化写法，并增加clean指令
```Makefile
CC = gcc
TARGET = main.exe
OBJS = main.o 1.o 2.o 
CFLAGS = -Wall -std=11

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

1.o: 1.h
2.o: 1.h

%.o: %.o
	$(CC) -c $(CFLAGS) $< -o $@
	
.PHONY: clean
clean: 
	rm -f $(TARGET) $(OBJS)
```

6、GDB调试一般用于排查什么问题？GDB的调试流程？
排查程序运行时错误, 函数调用, 运行时变量值.
gcc编译增加调试信息: `gcc -g main.c -o main`
开始gdb调试: `gdb main`
查看代码: `list`
打断点: `break 10`
打印变量值: `print a`
调用堆栈: `bt`
断点信息: `info breakpoint`
下一个断点: `continue`
下一步且不进入函数内: `next`
下一步进入函数内: 'step'
退出: `quit`

7、段错误是什么意思？产生段错误的原因有哪些？
访问内存报错. 段-分段 段错误就是分段报错. 访问了不属于程序的内存地址
如访问空指针, 野指针. 函数递归调用内存溢出. 访问数组越界等.


8、标准IO与文件IO的区别有哪些？
标准IO是由C语言库函数提供了的一些可以输入输出的函数`fopen fread fwrite fclose fgetc fgets fputc fputs` 有一套自己的缓存机制. 通过调用不同平台的IO函数, 实现数据的读写. 提供了一套流(stream)的操作. 是以用户态形式进行读写
文件IO在Linux系统下就是一系列针对文件描述符的输入输出操作`open write read` 适合大块的读写. 直接以内核态进行数据的读写.

9、标准IO的缓冲区有哪些？作用于哪里？刷新条件有哪些？为什么需要用到缓冲区？
行缓存(stdin stdout) 全缓存(fread fwrite) 无缓存(stderr)
刷新条件: 缓存区满 输入输出状态切换 fclose fflush 程序结束.
换行(行缓存)
防止频繁进行用户态 内核态的切换造成的系统不必要的开销.

10、动态库和静态库的区别？各有什么好处？
静态库: Linux下以.a结尾. 在链接阶段直接接入到程序中去, 不需要依赖. 
动态库: 以.so结尾. 需要存放到动态库中去, 环境变量中去, 方便被程序查找. 更新后不需要重新编译程序还能继续运行.