# 网络编程实现流程
***
## 服务端
***
`socket`函数创建一个套接字 文件描述符. 
`struct sockaddr_in` 新建一个IPv4的`socketaddr`结构体,填写服务器的地址 端口 网络协议等信息.
`bind` 函数将socket和服务器地址信息绑定.
`listen` 监听绑定后的文件描述符
`accept` 接收到客户端的`connect`请求成功, 生成新的文件描述符`connect_fd`
通过`connect_fd`来进行服务端 客户端的发送和接收数据.(由此可以得出TCP就是全双工通信, 即可以接收数据 也可以发送数据)
`recv` `send` 就是具体的发送和接收数据, 在TCP通信中, 也可以使用`read``send`文件IO来进行操作.

```
socket
  ↓
bind
  ↓
listen
  ↓
accept
  ↓
recv / send
  ↓
close
```


## 客户端
***
新建一个`socket`
填入服务器信息`struct sockaddr_in`
连接服务器`connect`
`recv` / `send`

![[file-20261009144156473.png]]

# 三次握手 & 四次挥手
***
## 三次握手
***
```Plain text
1. 客户端 connect()，发送 SYN
2. 服务端收到 SYN，回复 SYN + ACK，连接处于半连接状态
3. 客户端收到 SYN + ACK，回复 ACK
4. 服务端收到 ACK，三次握手完成
5. 连接进入已完成连接队列
6. accept() 取出连接，返回新的 connect_fd
7. 双方开始 send / recv
```
![[file-20261009151932075.png]]

## 四次挥手
***

![[file-20261009152557068.png]]