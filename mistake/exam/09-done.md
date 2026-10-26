# C 语言基础

姓名：__________  
开始时间：__________

---

## 1. 宏定义

用预处理指令 `#define` 声明一个常数，用以表明 1 年中有多少秒。

> 忽略闰年问题。

```
____________________________
```

---

## 2. 用变量 `a` 给出下面的定义

### a)

一个整型数。

> An integer

```
____________________________
```

### b)

一个指向整型数的指针。

> A pointer to an integer

```
____________________________
```

### c)

一个指向指针的指针，它指向的指针是指向一个整型数。

> A pointer to a pointer to an integer

```
____________________________
```

### d)

一个有 10 个整型数的数组。

> An array of 10 integers

```
____________________________
```

### e)

一个有 10 个指针的数组，该指针是指向一个整型数的。

> An array of 10 pointers to integers

```
____________________________
```

### f)

一个指向有 10 个整型数数组的指针。

> A pointer to an array of 10 integers

```
____________________________
```

### g)

一个指向函数的指针，该函数有一个整型参数并返回一个整型数。

> A pointer to a function that takes an integer as an argument and returns an integer

```
____________________________
```

### h)

一个有 10 个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数。

> An array of ten pointers to functions that take an integer argument and return an integer

```
____________________________
```

---

## 3. static 关键字

关键字 `static` 的作用是什么？

---

## 4. 找出代码中存在的问题

指出下面代码中存在的问题：

```
void test2()
{
    char string[10], str1[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        str1[i] = 'a';
    }

    strcpy(string, str1);
}
```

---

## 5. include 的区别

下面两种写法有什么区别？

```
#include <filename.h>
```

和：

```
#include "filename.h"
```

---

## 6. 字符串循环移动

编写一个函数，作用是把一个 `char` 组成的字符串循环右移 `n` 个。

例如原来是：

```
abcdefghij
```

如果：

```
n = 2
```

移动后应该是：

```
ijabcdefgh
```

函数定义如下：

```
// pStr 是指向以 '\0' 结尾的字符串的指针
// steps 是要求移动的 n

void LoopMove(char *pStr, int steps)
{
    // 请填充...
}
```

---

## 7. 求 sizeof

给定：

```
struct {
    short a1;
    short a2;
    short a3;
} A;

struct {
    long a1;
    short a2;
} B;
```

求：

```
sizeof(A) = ________

sizeof(B) = ________
```

---

## 8. 内存拷贝

写一个函数，完成内存之间的拷贝。

```
________________________________________
```