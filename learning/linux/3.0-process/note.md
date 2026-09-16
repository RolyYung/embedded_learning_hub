# 进程的总结
***

在进程的学习中, 我已经接触了几个概念 session process-group process.
也就是**会话** **进程组** **进程** 这三个概念.
下面是它们的关系: 
```markdown
                 Session
                    │
          ┌─────────┴─────────┐
          ↓                   ↓
     Process Group       Process Group
          │                   │
      ┌───┼───┐            ┌──┴──┐
      ↓   ↓   ↓            ↓     ↓
     P1  P2  P3           P4    P5

SID：我在哪个会话
PGID：我在哪个进程组
PID：我是哪一个进程
```

