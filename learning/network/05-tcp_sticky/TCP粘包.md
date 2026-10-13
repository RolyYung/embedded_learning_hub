***
TCP是面向数据流的, 有缓冲区, 所以不管是发送, 还是接收, 都可能会把两个数据包被整理到一起了.

```C
send("hello")
send("world")

// 粘包
recv(buf) // hello world
```

对应的就有**拆包**的概念:
```C
send("hello");
send("world");

// 粘包
recv(buf); // hel
recv(buf); // loworld
```

