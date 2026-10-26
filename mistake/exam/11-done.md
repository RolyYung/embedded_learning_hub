# C 语言技术交流

## 一、简答题

> 每小题 5 分，共 70 分

### 1. switch


```
不能做 `switch()` 的参数类型是（ ）。
```


---

### 2. “零值”比较

请填写以下变量与之对应的“零值”比较的 `if` 语句：

```
bool bTest;
float fTest;
char *pTest;
```

---

### 3. sizeof

以下为 Linux 下的 32 位 C 程序，请计算 `sizeof` 的值。

```
char str[] = "Hello";
sizeof(str) = (    );

char *p = str;
sizeof(p) = (    );

int n = 10;
sizeof(n) = (    );

void func(char str[100]);
sizeof(str) = (    );

void *p = malloc(100);
sizeof(p) = (    );
```

---

### 4. 找出代码问题

请问以下代码有什么问题：

```
int main()
{
    char a;
    char *str = &a;

    strcpy(str, "hello");

    printf(str);

    return 0;
}
```

---

### 5. 找出代码问题

请问以下代码有什么问题：

```
char *s = "AAA";

printf("%s", s);

s[0] = 'B';

printf("%s", s);
```

---

### 6. C 与 C++ 的 struct

C 和 C++ 中的 `struct` 有什么不同？

---

### 7. 数组和链表

数组和链表的区别？

---

### 8. strlen

以下函数打印结果是多少？

```
void main()
{
    char aa[10];

    printf("%d", strlen(aa));
}
```

---

### 9. 结构体大小

以下 `name1` 和 `name2` 分别占多少字节？

```
struct name1
{
    char str;
    short x;
    int num;
};
```

求：

```
sizeof(struct name1);
```

以及：

```
struct name2
{
    char str;
    int num;
    short x;
};
```

求：

```
sizeof(struct name2);
```

---

### 10. volatile

关键字 `volatile` 有什么含意？

并给出三个不同的例子。

---

### 11. 头文件防重复包含

头文件中的：

```
#ifndef
#define
#endif
```

是干什么用的？

---

### 12. include

以下两种写法有什么区别？

```
#include <filename.h>
```

和：

```
#include "filename.h"
```

---

### 13. const 与 static

`const` 有什么用途？

> 请至少说明两种。

`static` 有什么用途？

> 请至少说明两种。

---

### 14. 宏定义

写一个“标准”宏，这个宏输入两个参数并返回较小的一个。

```
________________________________________
```

---

# 二、编程题

> 共 30 分

## 1. 位操作

输入一个整数 `a`，取其从右端开始的第 4～7 位并输出。

> 5 分

---

## 2. 实现 strcmp

简单实现 `strcmp` 函数。

函数原型：

```
int strcmp(const char *str1, const char *str2)
{
    /* 请实现 */
}
```

> 5 分

---

## 3. 实现二分查找

实现二分查找。

函数原型：

```
int binary_search(int *arr, int key, int n)
{
    /* 请实现 */
}
```

> 10 分

---

## 4. 链表反向

把一个链表反向。

函数原型：

```
void reverse(test *pHead)
{
    /* 请实现 */
}
```

> 10 分