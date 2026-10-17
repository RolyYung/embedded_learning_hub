***
1、什么是高可靠通信？
```
数据 有序 不重复 准确的通信. 有超时 丢包检测的通信. 
```

2、TCP与UDP的区别有哪些？UDP如何实现可靠传输？
```
TCP就是可靠通信, 面向有连接. 三次握手 四次挥手机制
UDP无连接. 数据包传输. 不会出现粘包现象. 但不保证数据准确 重复 有序.

上层数据进行封装: ack data等. 详情见TFTP
```

3、如何区分A、B、C、D类地址
```
0
10
110
1110
```

4、IPv4与IPv6的区别是什么？（参考面试宝典）
```
32位地址. 有限. 头部内容比v6多. 支持组播 广播
128位地址. 几乎无限. 简化了头部. 更好支持了IPsec. 取消了广播
```
5、什么叫长连接？什么叫短连接？（参考面试宝典）
```
连接的时间长短.
连接后是否复用 还是 直接断开. 
在不同场景下, 长短连接都可以节省服务器资源.
```
***
1、简述三种超时检测的办法
```
setsockopt(socket, SOL_SOCKET, SO_RECVTIMEO/SO_SNDTIMEO)
alarm()
select() poll() epoll()
```

2、什么是粘包？如何解决粘包带来的问题
```
一次recv 多个send数据
1. 固定数据长度
2. 特殊字符分割
3. 前四个字节 固定作为数据长度表示.
```

3、解释以下名词含义，并说明其作用

• IP
```
网络寻址
IPv4 IPv6

```

• port
```
传输层用到. IP+port 就能确定应用程序, 准确来说就是具体套接字.
```

• 子网掩码（如何通过子网掩码制订当前网络下最多连多少台主机）
```
CIDE+mask (网络位 + 主机位)
2^32-mask-2
0网络地址
255广播地址
```

• DNS服务器
```
域名->ip的转换
经典服务器 8.8.8.8
```

• DHCP服务器
```
局域网主机地址分配
```

• 广播与组播
```
broadcast 
group
```

4、如何使用Wire shark抓取指定网卡的数据包，简述或演示抓取流程
```
支持筛选 ip 端口 协议
支持查看各个层的具体封装
```
***
1、说出OSI七层协议模型，并简述各层的功能
```
物理
数据 ARP 以太网(Ethernet)
网络 IP ICMP
传输 TCP UPD
会话 HTTP FTFP HTTPS DNS DHCP
表示
应用
```

2、说出TCP/IP 四层协议族，以及每层有哪些协议，最少写出8个协议

3、编写TCP服务器与客户端的代码框架（只编写函数名即可）
```
socket()
bind()
listen()

accept()
send()/recv()
close()
close()
```

4、TCP如何判断对方异常断电？
```
超过重传次数;
keep-alive;
心跳
```

5、当客户端连不上服务器时，如何排查错误？
```
网线 交互机等硬件
IP 端口错误
抓包工具确定数据问题
```
***
1、二层交换机的工作原理？
```
获取局域网MAC地址, 维护MAC表. 进行数据转发.
```

2、简述任意两种并发服务器的设计，并说明其优缺点以及容易出现的问题
```
多进程: 资源不共享. 继承的文件描述符需要及时关闭. 需要回收进程
多线程: 资源共享, 容易出现竞争临界资源. 不需要回收. 内存占用比多进程少
```

3、简述三种IO多路复用方法以及各自的特点
```
select: 数量有限, 每次都需要遍历
poll: 数量无限, 每次都需要遍历
epoll: 不需要遍历, 每次不需要遍历. 只返回需要跟进的文件描述符
```
***
1、简述五种IO模型，并说明是同步操作还是异步操作
```
阻塞
非阻塞
多路复用
信号IO
异步IO. 内核等待并处理数据. 只是通知程序状态.
```

2、路由器的工作原理？简述数据包发送出去的流程
```
网络寻址, 数据到路由器, 判断是否需要发出, 还是子网内转发
公网就需要找下一个路由节点, 修改数据包头部信息.
http->tcp->ip->Ethernet->internet

```

3、TCP三次握手与四次挥手的过程
```
a. SYN seq=x
b. SYN seq=y ACK ack=x+1
c. ACK ack=y+1

a. FIN seq=x
b. ACK ack=x+1
c. FIN seq=y
d. ACK seq=x+1 ack=y+1 
```
***
1、编写epoll多路复用TCP服务器代码（完整代码）（应用层考点）
```C
int listenfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockadd_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVERIP);

bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
listen(listenfd, 5);

struct epoll_event ev;
ev.data.fd = listenfd;
ev.events = EPOLLIN;

int epfd = epoll_create1(0);

epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

struct epoll_event events[MAX_EVENTS];
while(1){
	int ready_num = epoll_wait(epfd, events, MAX_EVENTS, -1);
	for(int i=0;i<ready_num;i++){
		int fd = events[i].data.fd;
		if(fd == listenfd){
			struct sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			
			int connfd = accept(listenfd, &client_addr, &client_len);
			ev.data.fd = connfd;
			ev.events = EPOLLIN;
			epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			continue;
		}else{
			char buf[BUF_SIZE];
			int nbytes = recv(fd, buf, BUF_SIZE, 0);
			if(nbytes == 0){
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
				close(fd);
				continue;
			}else if(nbytes < 0){
				perror("error");
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
				close(fd);
				continue;
			}else {
				printf("...");
			}
		}
	}
}
close(epfd);
close(listenfd);
return 0;
```

2、加密传输是如何实现的？OpenSSL 基本原理（课外，讲清楚密钥交换流程以及密钥作用）
```
sender: TLS版本 算法 临时公钥A. 
recv: 确定版本 算法. 临时公钥B.
sender&recv: 确定共享密钥 S

certern: 发送证书 公钥. 
certern: 之前通信内容(通过私钥签名)

recv: 解密后确认无误, 开始通信.
在TCP后, 进行了一次安全确认.

非对称 + 对称加密的组合
```

3、如何使用UDP实现TFTP协议（协议格式详细内容是什么？如何解决丢包、超时问题）
```
RRQ/WRQ-filename-mode
DATA-block
ACK-ack
ERROR-code

block 和 ack互相配合保证丢包问题不存在.
DATA发送时, 设置定时器, 保证超时问题.
```
