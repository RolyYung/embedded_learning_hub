#gdb 
# 前置知识
生成可以gdb调试的代码文件, 命令示例:
`gcc -g -o hello hello.c`
`-g`: debug information, 给这个编译的代码, 给一个源码地图. 前端打包也会有一个概念: source-map,差不多也是这个意思.
***
至于教材给的写法, 和普通的还是有点区别, 原因是gcc指令对参数顺序没有严格要求, 下面代码都是可以的:
`gcc hello.c -g -o hello`
`gcc -g hello.c -o hello`
`gcc -o hello -g hello.c`
***
唯一需要注意的是`-o hello`这个是绑定的,`hello`是`-o`的参数,其他的顺序都可以改变

# GDB调试命令
## gdb进入程序
***
`gdb asmd`

## 运行
***
`gdb run`
`gdb r`
> 使用全称更容易理解, 尽量使用全称, 这样就不是靠背,而是可以通过英文字面理解每个命令的作用

## 常用的命令
## continue
> 继续运行到程序结束/下一个断点

## list
展示代码. 可以指定文件名, 例子: `list main.c:20` - 展示main.c文件第二十行附近的代码
如果是多文件系统, 可以看下具体的源代码文件`info sources` - 这个命令可以查看所有的源文件, 调用文件

## b
设置断点. `b 10` 在第十行设置断点
`info b` 查看断点信息, 在哪些文件位置设置了断点
`delete 10` 删除点断, 删除编号为10的断点, 具体编号可以用`info`命令来查看

## bt
查看调用栈. backtrace.

## print display
展示变量值, print 用于单次的展示. display用于每次执行后都会展示对应的变量值.








