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
## 运行
`gdb run`
`gdb r`
> 使用全称更容易理解, 尽量使用全称, 这样就不是靠背,而是可以通过英文字面理解每个命令的作用