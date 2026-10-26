# 一维数组题目

## 题目一

### 指针移动

```c
#include <stdio.h>

int main(void)
{
    int a[] = {10, 20, 30, 40, 50};
    int *p = a;

    printf("%d\n", *p);
    printf("%d\n", *(p + 2));

    p++;

    printf("%d\n", *p);
    printf("%d\n", p[2]);

    return 0;
}
```

---

## 题目二

### 指针与下标

```c
#include <stdio.h>

int main(void)
{
    int a[] = {2, 4, 6, 8, 10};

    int *p = &a[2];

    printf("%d %d\n", p[-1], p[1]);

    *(p + 1) = 99;

    printf("%d\n", a[3]);

    printf("%td\n", p - a);

    return 0;
}
```

---

## 题目三

### 元素指针与数组指针

```c
#include <stdio.h>

int main(void)
{
    int a[5] = {1, 3, 5, 7, 9};

    int *p = a;

    int (*q)[5] = &a;

    int *pp = (int *)(&a + 1); // 还可以写成什么形式

    printf("%d\n", *(p + 2));

    printf("%d\n", (*q)[3]);

    printf("%d\n", *(*q + 4));

    printf("%d\n", pp[-1]);

    printf("%d\n", pp[-2]);

    printf("%d\n", *(pp - 2));

    return 0;
}
```