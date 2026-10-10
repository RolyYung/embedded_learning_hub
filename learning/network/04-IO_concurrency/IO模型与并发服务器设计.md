***
# 阻塞IO 与 非阻塞IO
***
区别就是等待与否
等待数据,数据没来就进入睡眠可中断状态, 就是阻塞IO
查询数据是否到来. 没到来就继续往下执行, 就是非阻塞IO

# IO 多路复用
***
IO多路复用是一种单线程或单进程管理多个文件描述符 （如套接字）的技术，核心是通过系统调用监视多个IO操作的状态，当某个IO操作就绪 （可读、可写或发生异常）时，通知应用程序进行处理
> 白话文理解: 监听多个IO操作状态, 有一个就绪了就会通知, 交给程序处理.

## 多路复用函数
***
### select
***
```C
int
     select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds,
         fd_set *restrict errorfds, struct timeval *restrict timeout);
```
`nfds`: `Example: If you have set two file descriptors "4" and "17", nfds should  not be "2",but rather "17 + 1" or "18".` 如果你已经设置了两个文件描述符, 4 17, `nfds`的值应该是18. 而不是2.
`readfds`,和后面的两个都是设置 读 写 错误文件描述符的集合. 
`timeout`: 设置超时时间. 一般都是NULL. NULL表示永久阻塞.

## poll
***
```C
int
     poll(struct pollfd fds[], nfds_t nfds, int timeout);
```
`fds[]`: `struct pollfd`集合
`nfds`: `The nfds argument specifies the size of the fds array.`
`timeout`: 超时时间. 单位是毫秒.


