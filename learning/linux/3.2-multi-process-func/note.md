# 多进程相关函数

## `getpid`
***
`pid_t getpid(void)`
> 获取当前进程的pid.

`man 2 getpid`

## `getppid`
***
`pid_t getppid(void)`
> 获取当前进程的父进程pid

## `exit`
***
`void exit(int status)`

属于`man 3`
`man 2`中有更底层的实现函数`_exit`


### 关于`status`
***

为什么需要一个`int`类型的status传入退出进程的函数呢?
我的理解: 需要知道进程结束时的状态, 如果是成功就是0, 如果是失败就需要给非零值,非零值就相当于`linux`内部的一些状态码(`errno`)

而且你传入的status会与0377做与操作(`status & 0377`)
也就是`status & 0xff`
虽然`0xff` 更能直观理解, 但在Unix世界里, 八进制一直是重要的单位. (不然0为什么给八进制, 其他的都需要加其他前缀`0x` `0b`)

C标准给了两个常量: `EXIT_SUCCESS` `EXIT_FAILURE`

## `_exit`
***
`void _exit(int status)`
本身是系统调用, C标准提供的两个常量也可以兼容使用.
和库函数`exit`最重要的区别是 `exit`会做一些前置的清理工作, `_exit`则会直接退出

# 资源回收类函数
***
## `wait`
***
`pid_t wait(int * wstatus)`
属于`man 2`

***
阻塞等待. 就是等待有任意一个子进程`exit`了才会继续后面的代码执行.
`wstatus` 用于接收自己成退出的`staus` 存入对应的内存中去.

对于`wstatus`的解析, 有专门的解析宏:
### 解析宏
就写三个吧, 不记了, 后面想用了可以直接查手册:
`man 2 wait` 里面把所有的解析宏都列出来了.
#### `WIFEXITED()`
判断是否是通过`exit` or `_exited` 函数正常退出的进程
#### `WEXITSTATUS()`
在上面这个为true时才能使用, 获取status的低八位作为最后返回值.

***
#### `WIFSIGNALED(wstatus)`
子进程是否被终止(`SIGKILL`等)

## `waitpid`
***
`pid_t waitpid(pid_t pid, int * status, options)`

相比于上面的`wait`函数, 可以选择无阻塞模式, 也可以指定进程 / 进程组.
总结: 操作更多 选择更多.

### `pid`
***
`>0`: 就是指定的子进程`pid`
`=0`: 同组的任意子进程
`-1`: 任意子进程
`<-1`: 组进程id=绝对值的进程

### `wstatus`
***
和`wait`函数一样

### `options`
***
`0`: 阻塞等待
`WNOHANG`: 非阻塞等待.未退出就返回0
`WUNTRACKED`: 捕获子进程暂停状态. 

# 文件描述符重定向函数
***
## `dup`
***
`int dup(int oldfd)`
复制一个已有的文件描述符.
**给已经打开的文件, 再配一把钥匙**
这两个文件描述符可以访问同一个文件.

返回值: -1 就是失败.
成功就是新的文件描述符. 文件描述符的数值按照最小来分配.

## `dup2`
***
`int dup2(int oldfd, int newfd)`
用于指定文件描述符. 如果`newfd`已经存在, 则会静默关闭后再打开.

# 进程程序替换函数
***
## `exec`函数族
***
### `execlp`
***
`int execlp(const char * file, ..., NULL)`
> 在PATH里找到`file`对应的命令/程序, 执行后面的参数, NULL作为结束符

理解: 
`exec` execute 执行
`l` list 列出
`p` PATH

成功就无返回
失败就会返回-1

### `execvp`
***
`int execvp(const char * file, char * const arg[])`

理解:
`v` vector. 这里指的是数组. 在数学领域指的是向量.