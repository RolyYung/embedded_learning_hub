***
1、什么是高可靠通信？
```
数据有序 不重复 不遗漏. 有超时重发机制. 确保数据的准确传输
```

2、TCP与UDP的区别有哪些？UDP如何实现可靠传输？
```
TCP: 可靠通信, 有三次握手 四次挥手机制. 以字节流形式, 会出现粘包
UDP: 无连接, 不确保数据准确. 以数据包形式. 

UDP实现可靠传输: 上层应用层实现封装. UDP数据包中加入ACK 数据包编码等.
```

3、如何区分A、B、C、D类地址
```
0开头: A类
10开头: B类
110开头: C类
1110开头: D类
```

4、IPv4与IPv6的区别是什么？（参考面试宝典）
```
IPv4: 32位地址长度, 地址有限, 头部开销大.
IPv6: 128地址长度, 地址无限. 取消了检验和等头部信息, 取消了广播机制, 使用更精准的组播.对IPsec支持更好.
```

5、什么叫长连接？什么叫短连接？（参考面试宝典）
```
长连接: 完成连接通信后, 不会立马断开, 后面数据一直通过这个连接, 避免反复开辟连接的资源浪费. 适合相同连接多的功能
短连接: 完成通信后, 就断开, 不占连接资源. 适合一次性任务.
```
***
1、简述三种超时检测的办法
```
alarm()定时器函数.
select poll等多路复用函数自带的定时器.

setsockopt(socket, SOL_SOCKET, SO_RECVTIMEO/SO_SNDTIMEO)

```

2、什么是粘包？如何解决粘包带来的问题
```
粘包: 一次recv 接收到 多次send的数据
解决: 1. 定长 2. 特殊字符做分隔 3. 数据层做封装, 前四字节做数据长度说明.
```

3、解释以下名词含义，并说明其作用

• IP
```
Internet protocol. 负责网络寻址 路由跳转等. 互联网基础. 目前IPv4 IPv6两个版本
```

• port
```
传输层需要用的, 确定设备和进程. 不同的传输层协议的端口互不影响. 
```

• 子网掩码（如何通过子网掩码制订当前网络下最多连多少台主机）
```
现代网络不按照传统A类地址, 而是按照CIDR/子网掩码 确定网络位和主机位.
2^32-mask - 2就是最多主机数
0 是网络地址
255是广播地址
```

• DNS服务器
```
域名->ip地址.
```

• DHCP服务器
```
动态配置主机IP的地址
```

• 广播与组播
```
广播:局域网内的所有设备都会消息
组播:接入指定组 才会收到消息
```

4、如何使用Wire shark抓取指定网卡的数据包，简述或演示抓取流程
```
选择网卡: 稍显IP 端口 协议
```
***
1、说出OSI七层协议模型，并简述各层的功能
```
物理层
数据链路层 以太网协议 ARP
网络层IP ICMP
传输层TCP UPD
会话层
表示层
应用层HTTP DNS TFTP ICHP
```

2、说出TCP/IP 四层协议族，以及每层有哪些协议，最少写出8个协议

3、编写TCP服务器与客户端的代码框架（只编写函数名即可）
```
socket()
bind()
listen()

accept()
recv()/send()
close()
```

4、TCP如何判断对方异常断电？
```
超过最大重传次数. 就会断联
长时间没有通信, 会有keepalive机制, 还有心跳机制来检测是否还在连接
```

5、当客户端连不上服务器时，如何排查错误？
```
物理层: 硬件问题. 网线 交换机等断电.
网络层: IP是否正确
传输层: 端口是否正确
通过网络抓包 检查数据是否发送 握手是否成功
```
***
1、二层交换机的工作原理？
```
通过维护MAC表, 对局域网数据的进行转发.
没有找到, 就会去泛红式传播, 找到对应MAC地址记录.
```

2、简述任意两种并发服务器的设计，并说明其优缺点以及容易出现的问题
```
多进程: 资源不共享, 需要及时close(), 避免占用连接资源. 内存开销大
多线程: 资源共享, 但会出现临界资源竞争状态. 内存开销小.
```

3、简述三种IO多路复用方法以及各自的特点
```
select: 位图机制, 每次更新需要遍历. 数量有限
poll: 链表存储, 数量没限制. 但还是需要遍历
epoll: 内核通知, 不需要遍历, 没数量限制. 适合 大量文件复用.
```
***
1、简述五种IO模型，并说明是同步操作还是异步操作
```
阻塞
非阻塞
信号
多路复用
异步IO: 把信息交给内核. 只接收消息了,知道是否完成. 不需要由进程来完成了. 异步.上面都是同步. 
```

2、路由器的工作原理？简述数据包发送出去的流程
```
网络层的网络寻址和路径查询
数据->传输层头部->网络层封装->以太网帧封装
路由->拆开网络层获取IP, -> 确定下一个路由点->IP层封装 -> 以太网封装-> 发送.
```

3、TCP三次握手与四次挥手的过程
```
三次握手:
a. SYN seq=x
b. SYN seq=y ACK ack=x+1
c. ACK ack=y+1

四次挥手:
a. FIN seq=x
b. ACK ack=x+1
c. FIN seq=y ack=x+1
d. ACK seq=x+1 ack=y+1
```
***
1、编写epoll多路复用TCP服务器代码（完整代码）（应用层考点）
```C
int listenfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
listen(listenfd, 5);

int epfd = epoll_create1(0);
struct epoll_event ev = {0};
ev.data.fd = listenfd;
ev.events = EPOLLIN;

epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

strcut epoll_event epoll_events[MAX_EVENTS];
while(1){
	int ready_num = epoll_wait(epfd, epoll_events, MAX_EVENTS, -1);
	for(int i=0; i<ready_num; i++){
		int fd = epoll_events[i].data.fd;
		if(fd == listenfd){
			struct sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			int connectfd = accept(listenfd, (struct sockaddr_in*)&sockaddr_client, &client_len);
			
			ev.data.fd = connectfd;
			ev.events = EPOLLIN;
			epoll_ctl(epfd, EPOLL_CTL_ADD, connectfd, &ev);
			
			continue;
		}else{
			char buf[BUF_SIZE];
			int nbytes = recv(fd,buf, BUF_SIZE,0);
			if(nbytes == 0){
				ev.data.fd = fd;
				ev.events = EPOLLIN;
				epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
				close(fd);
			}else {
				send(fd, buf, BUF_SIZE, 0);
			}
		}
	}
}
close(listenfd);
close(epfd);
```

2、加密传输是如何实现的？OpenSSL 基本原理（课外，讲清楚密钥交换流程以及密钥作用）
```
sender 发出TLS版本, 支持算法, 临时公钥A.
receiver 接收请求, 发出选择的TLS版本, 算法, 临时公钥B
各自在接收消息后, 能够得出同一个通信密钥.
后续通过这个通信密钥加密数据.

认证阶段: 防止攻击者伪装服务器, 发送数据.
receiver还会给出CA证书, 域名 & 公钥. 通过私钥签名, 把这之前的通信消息也一起加密发送.
sender拿到证书和公钥和解密, 确认服务器安全.

密钥的前期作用是用来做非对称加密, 确保信息只有双方能理解.
后期用对称加密, 解密 传输速度也是最快的.
```

3、如何使用UDP实现TFTP协议（协议格式详细内容是什么？如何解决丢包、超时问题）
```
通过操作码RRQ WRQ实现上传 下载功能
通过DATA实现数据包的顺序发送
通过ACK实现丢包 超时等问题的补充
ERROR错误

操作码占两个字节大小
DATA block包数据占两个字节大小
ACK 确认码也占两个字节大小
ERROR后接错误码. 占两个字节大小

RRQ WRO后接filename 接 mode(普遍使用octet)

解决丢包超时问题: 发送端每次发送数据, 会设置定时器, 超时没有收到ACK码就会重发.
丢包: 在收到ACK和当前block编号不匹配, 也会重发.
```
