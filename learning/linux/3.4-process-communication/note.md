# 进程通信笔记

## 无名管道


## 有名管道
***
缓存区大小是64KB

库函数`mkfifo` : `man 3 mkfifo`
shell 命令也有`mkfifo`: `man 1 mkfifo`
库函数调用的是linux提供的另一个函数:`mknodat`来实现有名管道的创建.


