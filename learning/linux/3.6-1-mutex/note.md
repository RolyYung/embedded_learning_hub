互斥锁

线程1: 加锁-> 加锁成功-> 处理数据 -> 处理完毕 -> 广播通知 -> 解锁 -> 退出

线程2: 加锁 -> 加锁成功 -> 读取数据 -> 读取完毕 -> 解锁 -> 退出

```markdown
消费者 thread_2                         生产者 thread_1
────────────────                       ────────────────

lock(mutex)
    │
    ▼
拿到 mutex
    │
    ▼
检查 flag
    │
    ▼
 flag == 0
    │
    ▼
cond_wait(cond, mutex)
    │
    ├── ① 释放 mutex ──────────────────────►
    │                                      │
    │                                      ▼
    │                                  lock(mutex)
    │                                      │
    │                                      ▼
    │                                   拿到锁
    │                                      │
    │                                      ▼
    │                                   sleep(3)
    │                                      │
    │                                      ▼
    │                                  data = 1234
    │                                  flag = 1
    │                                      │
    │                                      ▼
    │                                  broadcast(cond)
    │                                      │
    │         ◄────────── 唤醒 ─────────────┘
    │
    │                    但是 mutex 还在生产者手里
    │                                      │
    │                                      ▼
    │                                  unlock(mutex)
    │                                      │
    ▼                                      │
重新竞争 mutex ◄────────────────────────────┘
    │
    ▼
拿到 mutex
    │
    ▼
cond_wait() 返回
    │
    ▼
重新检查 while(!flag)
    │
    ▼
 flag == 1
    │
    ▼
跳出 while
    │
    ▼
读取 data = 1234
    │
    ▼
flag = 0
    │
    ▼
unlock(mutex)
```

```markdown
生产者 thread_1                         消费者 thread_2
────────────────                       ────────────────

lock(mutex)
    │
    ▼
拿到 mutex
    │
    ▼
sleep(3)
    │
    │                                  lock(mutex)
    │                                      │
    │                                      ▼
    │                                  锁被占用
    │                                      │
    │                                   阻塞等待
    │                                      │
sleep结束                                 │
    │                                      │
    ▼                                      │
data = 1234                               │
flag = 1                                  │
    │                                      │
    ▼                                      │
broadcast(cond)                            │
    │                                      │
    ▼                                      │
unlock(mutex)                              │
    │                                      │
    └─────────────────────────────────────►│
                                           ▼
                                       拿到 mutex
                                           │
                                           ▼
                                       lock() 返回 0
                                           │
                                           ▼
                                       while(!flag)
                                           │
                                           ▼
                                        flag == 1
                                           │
                                           ▼
                                       不进入 wait
                                           │
                                           ▼
                                       消费 data
```