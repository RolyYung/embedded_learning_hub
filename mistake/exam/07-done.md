# 浙江迪捷软件科技有限公司 C 语言笔试题

## 一、填空题

### 1. 一维数组初始化

以下不能对一维数组 `a` 进行正确初始化的语句是 ________。

A.

```c
int a[10] = (0, 0, 0, 0);
```

B.

```c
int a[10] = {};
```

C.

```c
int a[] = {0};
```

D.

```c
int a[10] = {10 * 1};
```

---

### 2. 逻辑运算

若执行以下程序段后，则 `n` 的值是 ________。

```c
int a = 1, b = 2, m = 2, n = 2;

(m = a > b) && ++n;
```

A. 1  
B. 2  
C. 3  
D. 4

---

### 3. 自增运算

以下程序的运行结果是 ________。

```c
#include <stdio.h>

int main(void)
{
    int m = 5;

    if (m++ > 5)
        printf("%d\n", m);
    else
        printf("%d\n", m++);

    return 0;
}
```

---

### 4. 指针与地址

下列程序执行的两次打印结果是：

```text
（1）________
（2）________
```

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    int a;
    int *p;

    p = &a;

    *p = 0x500;

    a = (int)(*(&p));

    if (a == (int)p)
        printf("equal!\n");
    else
        printf("not equal!\n");

    a = (int)(&(*p));

    if (a == (int)p)
        printf("equal!\n");
    else
        printf("not equal!\n");

    return 0;
}
```

---

### 5. scanf 格式符

在 `scanf()` 函数的格式说明符中，长整型数的输入格式符是 ________。

A. `%lf`  
B. `%ld`  
C. `%d`  
D. `%x`

---

### 6. for、break 与 continue

下面程序的输出结果是 ________。

```c
int main(int argc, char *argv[])
{
    int a = 1, b;

    for (b = 1; b <= 10; b++)
    {
        if (a >= 8)
            break;

        if (a % 2 == 1)
        {
            a += 3;
            continue;
        }

        a -= 3;
    }

    printf("%d\n", b);

    return 0;
}
```

---

### 7. 字符指针

下面程序的输出结果是 ________。

```c
int main(int argc, char *argv[])
{
    const char *p = "12345";
    const char **q = &p;

    *q = "abcde";

    const char *s = ++p;

    p = "XYZWVU";

    printf("%c\n", *++s);

    return 0;
}
```

---

### 8. 结构体与地址偏移

以下代码打印的结果是 ________。

> 假设运行在 32bit x86 系列计算机上。

```c
struct st_t
{
    int status;
    short *pdata;
    char errstr[32];
};

struct st_t st[16];

char *p = (char *)(st[2].errstr + 32);

printf("%d", p - (char *)st);
```

---

### 9. sizeof

求以下各情况下 `sizeof(p)` 的值。

#### （1）

```c
char *p = "hello!";
```

#### （2）

```c
char p[] = "hello!";
```

#### （3）

```c
void *p = malloc(100);
```

---

### 10. 内存布局

内存布局问题：

```text
stack
heap
data
bss
```

写出下列所有定义的变量在内存中的位置。

```c
#include <stdio.h>

int a = 0;
int b;

extern int x;

static char c, y = 'C';

int main(int argc, char *argv[])
{
    char d = 4;

    static short e, f = 0x23;

    char *p = (char *)malloc(20);

    printf("a=%d, b=%d, c=%d, d=%d, e=%d",
           a, b, c, d, e);

    return 0;
}
```

填写：

```text
stack:

heap:

data:

bss:
```

---

# 二、判断题

### 1.

有数组定义：

```c
int a[2][2] = {{}, {2, 3}};
```

则：

```c
a[0][1]
```

的值为 `0`。

（ ）

---

### 2.

```c
int (*ptr)();
```

则 `ptr` 是一维数组的名字。

（ ）

---

### 3.

指针在任何情况下都可进行：

```text
>
<
>=
<=
==
```

运算。

（ ）

---

### 4.

```c
switch(c)
```

语句中，`c` 可以是以下类型：

```text
int
long
char
float
unsigned int
```

（ ）

---

# 三、问答题

## 1. 内存与指针问题

给出以下程序的运行结果并说明原因。

### （1）

```c
void GetMemory(char *p)
{
    p = (char *)malloc(100);
}

void Test(void)
{
    char *str = NULL;

    GetMemory(str);

    strcpy(str, "hello world");

    printf(str);
}
```

---

### （2）

```c
char *GetMemory(void)
{
    char p[] = "hello world";

    return p;
}

void Test(void)
{
    char *str = NULL;

    str = GetMemory();

    printf(str);
}
```

---

### （3）

```c
void GetMemory(char **p, int num)
{
    *p = (char *)malloc(num);
}

void Test(void)
{
    char *str = NULL;

    GetMemory(&str, 100);

    strcpy(str, "hello");

    printf(str);
}
```

---

### （4）

```c
void Test(void)
{
    char *str = (char *)malloc(100);

    strcpy(str, "hello");

    free(str);

    if (str != NULL)
    {
        strcpy(str, "world");

        printf(str);
    }
}
```

请问运行 `Test` 函数会有什么样的结果？为什么？

```text
(1) ____________________________________________________________

(2) ____________________________________________________________

(3) ____________________________________________________________

(4) ____________________________________________________________
```

---

## 2. 字符串常量

请问以下代码有什么问题？如何改正？

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *str = "Hehehe";

    strcpy(str, "hello");

    printf(str);

    return 0;
}
```

---

# 四、编程题

## 1. 实现 strcpy

不使用库函数，编写 `strcpy` 函数。

已知 `strcpy` 函数的原型是：

```c
char *strcpy(char *strDest, const char *strSrc);
```

其中：

```text
strDest：目的字符串
strSrc ：源字符串
```