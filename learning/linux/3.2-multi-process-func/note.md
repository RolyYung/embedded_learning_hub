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
#### `WIFEXITED()`
判断是否是通过`exit` or `_exited` 函数正常退出的进程
#### `WEXITSTATUS()`
在上面这个为true时才能使用, 获取status的低八位作为最后返回值.



