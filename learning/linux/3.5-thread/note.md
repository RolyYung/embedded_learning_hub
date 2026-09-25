线程相关

# 摘要
***
Linux没有"线程"这个数据结构.
在Linux下本质是轻量级进程(light weight process- `LWP`)

都是通过`struct task`来实现的.
但线程共享进程的空间和资源, 只有独立的栈和程序技术器.
一个线程崩溃可能导致整个进程崩溃

所有线程的函数都需要引入`pthread.h`
线程单词是`thread` 之所以加上`p`  `p->POSIX标准`
`POSIX` -> `Portable Operate System Interface X` 可移植操作系统接口标准(`X`是继承`Unix`的命名规则)
# `pthread_create`
***
```C
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
```
创建线程函数
参数: 
`thread`: `tid`值的指针(因为是一个`long` 类型)
`attr`: 线程的属性, 一般设置为`NULL`, 如果有需要, 可以后续动态设置
`start_routine`: 线程执行函数
`arg`: 函数执行所需要的参数

返回值:
成功: 0
失败: >0; `error number` 不会重置内核的`errorno`


# `pthread_join()`
***
join英文意思是`加入,参加`的意思.
在线程中这个函数的意思是等待子线程和主线程`汇合`
是一种阻塞等待.