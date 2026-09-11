# fopen
***
`man 3 fopen` linux系统下查看fopen使用手册
`FILE * fopen(const char * pathname, const char * mode)`
返回值: `FILE *` 用于操控文件流, 如果失败会返回`NULL`
参数: `pahtname` 字符串, 文件路径, 相对路径/绝对路径都可以
`mode` 字符串, 打开文件的方式: 读/写

***
## mode
| 字符串 | 功能                    |
| --- | --------------------- |
| r   | 只读,如果没有该文件就会报错        |
| r+  | 读写,没有该文件就会报错          |
| w   | 写,没有就会创建,有的话就会清空      |
| w+  | 读写,没有就会创建,有的话就会清空     |
| a   | 写,没有就创建,有的话就在文件末尾追加内容 |
| a+  | 读写,没有就创建,有的话就在文件末尾追加  |

# fclose
***
`int fclose(FILE * stream)`
关闭文件
成功返回0, 失败返回EOF(-1), 重置错误码.


# 内核中的错误码
***
Linux系统中, 内核通过预定义宏标识了一系列常见错误,错误码是正整数,但在内核传递中用负整数.
> 目前只需要知道 错误码都是正整数, 不同的数值表示着不同的错误.

## `strerror`
***
既然每个错误码都表示着不同的错误, 那么就会有对应的"翻译器"
`strerror` 就是这个翻译器. 将错误码翻译成对应的字符串展示到终端
这个需要引用`<string.h>` 库

## `perror`
***
有时候我们不仅仅需要展示系统自带的错误信息, 还需要在这个基础上, "添油加醋"一下,
这就是`perror` 这个函数的作用
用法:
`perror("发生了错误: ")`
***
这个的作用我的理解就是 `发生了错误: + strerror()`


# 读函数

## `fgetc`
***
`int fgetc(FILE * stream)`
***
接收文件流参数
返回值:
	成功: 返回的就是读取的字符的unsigned char值(转成了int值)
	失败: 返回EOF. 

## `fgets`
***
`char * fgets(char * s, int size, FILE * stream)`
***
返回值: 
	成功: 返回读取到的字符串
	失败: 返回NULL
参数:
	`char * s` 接收的字符串
	`int size` 字符串的大小
	`FILE * stream` 流
碰到`\n`就会终止,会读取`size-1`个字符,最后一个字符自动填充为`\0`


# 写函数

## `fputc`
***
`int fputc(int ch, FILE * stream)`
***
返回值:
	成功: 返回写入的字符的int值
	失败: 返回`EOF`
参数:
	`int ch`: 要录入的字符
	`FILE * steam`: 录入的字节流

## `fputs`
***
`int fputs(const char * s, FILE * stream)`
***
返回值:
	成功: 非零值,表示写入成功
	失败: 返回EOF
参数:
	`const char * s, FILE * stream` : 要写入的字符串 & 文件流

# 练习题

![[file-20260910192631897.png]]


