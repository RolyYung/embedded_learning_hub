# Linux 基础及 C 高级

## 一、选择题

> 每小题 2 分，共 40 分

### 1. Ubuntu 用户权限

Ubuntu 系统默认的（ ）用户对整个系统拥有完全的控制权。

A. root  
B. guest  
C. administrator  
D. supervistor

---

### 2. Shell 全局变量

下面哪个命令是用来定义 shell 的全局变量（ ）

A. exportfs  
B. alias  
C. exports  
D. export

---

### 3. 用户密码信息

哪个目录存放用户密码信息（ ）

A. `/boot`  
B. `/etc`  
C. `/var`  
D. `/dev`

---

### 4. 通配符

假设目录中存在若干文件：

```text
file_num.txt
```

其中 `num` 表示文件编号 1~10。

使用以下哪个通配符可以挑选出其中编号为 1、3、5 的文件？

A. `file_*.txt`  
B. `flie_?.txt`  
C. `file_[135].txt`  
D. `file_[^135].txt`

---

### 5. 文件权限

文件权限：

```text
r-x-wxr--
```

对应的八进制表示形式为（ ）

A. 0536  
B. 0654  
C. 0656  
D. 0534

---

### 6. C 语言运算符

在 C 语言中，要求运算数必须是整型的运算符是（ ）。

A. `/`  
B. `++`  
C. `!=`  
D. `%`

---

### 7. if 语句

执行下面语句后的输出结果为（ ）。

```c
int i = -1;

if (i <= 0)
    printf("****\n");

i = 2;

else
    printf("%%%%\n");
```

A. `****`  
B. `%%`  
C. `%%%%`  
D. 有语法错误，不能正确执行

---

### 8. 结构体 sizeof

结构体 `DATA` 定义如下：

```c
struct DATA
{
    float f1;
    int i;
    char c2;
};
```

则：

```c
sizeof(struct DATA)
```

的值为（ ）。

A. 6  
B. 8  
C. 12  
D. 16

---

### 9. static 与全局变量

下述程序第二次的输出结果为（ ）。

```c
int main(void)
{
    extern int a;

    int b = 0;
    static int c;

    a += 3;

    other();

    b += 3;

    other();
}

int a = 5;

other()
{
    int b = 3;
    static int c = 2;

    a += 5;
    b += 5;
    c += 5;

    printf("%d,%d,%d\n", a, b, c);

    c = b;
}
```

A. `13,0,13`  
B. `18,8,13`  
C. `13,8,13`  
D. `18,8,0`

---

### 10. 删除字符串中的字符

以下程序的功能是将字符串 `s` 中所有字符 `c` 删除。

空白处缺少的语句为（ ）。

```c
#include <stdio.h>

int main(void)
{
    char s[80];
    int i, j;

    gets(s);

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != 'c')
            ______________________;

    s[j] = '\0';

    puts(s);

    return 0;
}
```

A.

```c
s[j++] = s[i];
```

B.

```c
s[++j] = s[i];
```

C.

```c
s[j] = s[i];
j++;
```

D.

```c
s[j] = s[i];
```

---

### 11. 数组指针

若有说明：

```c
int (*p)[3];
```

以下叙述正确的是（ ）

A. `p` 是指针数组  

B. `(*p)[3]` 和 `*p[3]` 等价  

C. `p` 是指向一维数组中任何一个元素的指针  

D. `p` 是指向含有 3 个整型元素的一维数组的指针

---

### 12. 返回局部数组地址

下面程序运行的结果为（ ）。

```c
char *RetMenory(void)
{
    char p[] = "hello world";

    return p;
}

void Test(void)
{
    char *str = NULL;

    str = RetMemory();

    puts(str);
}
```

A. 语法错误，不能编译  
B. `hello world`  
C. 结果不可预知  
D. `hello world + 乱码`

---

### 13. 字符串函数

下面函数的功能是（ ）。

```c
int fun(char *x)
{
    char *y = x;

    while (*y++);

    return (y - x - 1);
}
```

A. 求字符串的长度  
B. 比较两个字符串的大小  
C. 将字符串 `x` 复制到字符串 `y`  
D. 将字符串 `x` 连接到字符串 `y` 后面

---

### 14. 表达式计算

若已定义 `x` 和 `y` 是整型变量：

```c
x = 2;
```

则表达式：

```c
y = 2.75 + x / 2;
```

的值是（ ）。

A. 5.5  
B. 5  
C. 3  
D. 4.0

---

### 15. 复合赋值

执行下列程序段后的输出结果是（ ）。

```c
int x = 1, y = 1, z = 1;

x += y += z;

printf("%d\n", x < y ? y : x);
```

A. 3  
B. 2  
C. 1  
D. 4

---

### 16. 有符号与无符号运算

下面的代码输出是（ ）。

```c
void foo(void)
{
    unsigned int a = 6;
    int b = -20;

    (a + b > 6)
        ? puts("> 6")
        : puts("<= 6");
}
```

A. `> 6`  
B. `<= 6`  
C. 段错误  
D. 结果未知

---

### 17. 符号链接

假设文件 `fileA` 的符号链接为 `fileB`。

删除 `fileA` 后，下面的描述正确的是（ ）。

A. `fileB` 也随之被删除  

B. 因为 `fileB` 未被删除，所以 `fileA` 会被系统自动重新建立  

C. `fileB` 会随 `fileA` 的删除而被系统自动删除  

D. `fileB` 仍存在，但是属于无效文件

---

### 18. 指针地址运算

```c
unsigned short *a = (unsigned short *)0x800;
unsigned short *b = a + 1;
```

则 `b` 的值为（ ）。

A. `0x800`  
B. `0x801`  
C. `0x802`  
D. `0x804`

---

### 19. for 循环

下面程序段的运行结果是（ ）。

```c
for (i = 1; i <= 5;)
    printf("%d", i);

i++;
```

A. `12345`  
B. `1234`  
C. `15`  
D. 无限循环

---

### 20. static 全局变量

在一个 C 源程序文件中，若要定义一个只允许本源文件中所有函数使用的全局变量，则该变量需要使用的存储类别是（ ）。

A. `extern`  
B. `register`  
C. `auto`  
D. `static`

---

# 二、填空题

> 每小题 2 分，共 10 分

## 1. 条件表达式

条件：

```text
2 < x < 3 或 x < -10
```

对应的 C 语言表达式为：

```text
____________________________
```

---

## 2. 指针数组

若有以下定义和语句：

```c
int *p[3], a[6], i;

for (i = 0; i < 3; i++)
    p[i] = &a[2 * i];
```

则：

```c
*p[0]
```

引用的是 `a` 数组元素中的：

```text
________________
```

而：

```c
*(p[1] + 1)
```

引用的是 `a` 数组元素中的：

```text
________________
```

---

## 3. 二维数组与数组指针

若有以下输入：

```text
1,2<CR>
```

其中 `<CR>` 代表回车换行符。

下面程序的运行结果为：

```text
________________
```

程序：

```c
int main(void)
{
    int a[3][4] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12
    };

    int (*p)[4], i, j;

    p = a;

    scanf("%d,%d", &i, &j);

    printf("%d\n", *(*(p + i) + j));

    return 0;
}
```

---

## 4. GCC 编译过程

GCC 的编译步骤按先后顺序分别为：

```text
________________________________________
```

```
预处理 -> 编译 -> 汇编 -> 链接 -> 可执行文件
-e -S -c -o
```

---

## 5. Make 工程管理

`make` 工程管理器根据：

```text
____________________________
```

来自动发现更新过的文件，从而减少编译的工作量。

---

# 三、编程题

> 第一题 10 分，其他两题各 20 分

## 1. 删除字符串中的空格

将一个字符串中所有的空格符删去。

例如：

原字符串：

```text
abc de fg
```

删除后的字符串：

```text
abcdefg
```

---

## 2. 字符串加密

编程实现对键盘输入的英文句子进行加密。

加密方法：

当内容为英文字母时，使用该字母在 26 个英文字母中其后的第 3 个字母代替。

若为其他字符，则保持不变。

例如：

```text
abcdef123
```

加密后：

```text
defghi123
```

又如：

```text
xyz123
```

加密后：

```text
abc123
```

---

## 3. 查找最长单词

编程在一个已知字符串中查找最长单词。

假定字符串中只包含：

- 字母
- 空格

空格用于分隔不同单词。

例如：

```c
char str[] = {
    "ASEEsdffw WEsdfe joiejorjerojeojr ASOJGWOEJIOJERJJhjnfd wejr"
};
```

最长字符串为：

```text
ASOJGWOEJIOJERJJhjnfd
```