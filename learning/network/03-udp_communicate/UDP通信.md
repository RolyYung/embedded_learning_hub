***
流程: 服务端挂起等待客户端发送消息 -> 客户端发送消息(sendto) -> 服务端接收消息(recvfrom)

![[file-20261010145842497.png]]

# UDP通信
***
分为一对一, 一对多(组播), 一对所有(广播). 

## recvfrom
***
接收函数
```C
ssize_t recvfrom(int socket, void *restrict buffer, size_t length, int flags,
         struct sockaddr *restrict address,
         socklen_t *restrict address_len);
```
`socket`: 用`socket`承接来的数据, `buffer` 数据缓冲, `length`缓冲区大小, `flags`标志位(目前没碰到过特殊处理, 一般就是0即不设置),`address` 发送端网络地址, `address_len`网络地址长度, 这里需要是指针,  因为发送端的网络地址一般我们都不清楚, 只有发送来了才会知道具体信息, 所以可能会修改.

返回值: 成功就是返回接收到的字节数, 失败则返回-1;

## sendto
***
发送函数
```C
ssize_t
     sendto(int socket, const void *buffer, size_t length, int flags,
         const struct sockaddr *dest_addr, socklen_t dest_len);
```

`socket`: 发送所需要的套接字
`buffer`: 发送的数据
`length`: 发送的数据长度
`flags`: 标志位. 0就是不设置
`dest_addr`: 目标地址
`dest_len`: 目标地址长度.

## setsockopt
***
配置`socket`. 比如加入组播, 设置ttl等.
这个感觉很少用到, 就暂不深究了. 只有在组播 广播的实现中会用到.
