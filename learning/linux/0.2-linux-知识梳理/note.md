# UNIX & BSD & System V
***
现在学习到的Linux知识, 都不能绕开这几个系统.
Unix是老祖, BSD 和 System V都是分支
而Linux都是借助Unix的发展, 受到了很多这些系统 分支的影响. 所以很多接口和函数实现 函数名都是可以从他们这些历史系统中有迹可循

## BSD
***
伯克利软件分支
最常见的就是`socket` 
Linux实现了这个功能

## System V
***
最常见的就是`IPC` 进程间通信
共享内存等都是由这个系统分支提出来的.

# `POSIX`
***
在分支越来越多的情况, 功能实现越来越多, 要记的函数名也越来越多了, 就有了这个标准, 中文翻译就是**可移植操作系统接口X**(portable operating system interface X), 这个X就是Unix风格的命名方式

Linux就是实现了大部分`POSIX`接口, 同时有些也会兼容那些历史上很重要的系统分支实现. 

