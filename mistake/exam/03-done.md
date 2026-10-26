# 二维数组题目

## 题目一

### 指针表达式

写出程序的输出，并把三个 `printf` 中的取值表达式分别改写成 `a[i][j]` 的形式。

```c
#include <stdio.h>

int main(void)
{
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("%d\n", *(*(a + 1) + 2));

    printf("%d\n", (*(a + 1))[0]);

    printf("%d\n", *(a[0] + 1));

    return 0;
}
```

---

## 题目二

### 指向一行的指针

```c
#include <stdio.h>

int main(void)
{
    int a[3][2] = {
        {10, 20},
        {30, 40},
        {50, 60}
    };

    int (*p)[2] = a;

    printf("%d\n", p[1][0]);

    p++;

    printf("%d\n", (*p)[1]);

    printf("%d\n", p[1][0]);

    printf("%td\n", p - a);

    return 0;
}
```

---

## 题目三

补全函数，使程序输出二维数组所有元素的和。

取值处使用指针运算。

```c
#include <stdio.h>

int sum(________________, int rows)
{
    int total = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            total += ________________;
        }
    }

    return total;
}

int main(void)
{
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("%d\n", sum(a, 2));

    return 0;
}
```

---

## 题目四

```c
#include <stdio.h>

int main()
{
    int arr[2][4] = {
        {1, 3, 5, 7},
        {2, 4, 6, 8}
    };

    int (*p)[4] = arr;

    printf("%d %d\n", *(*p + 2), *(*(p + 1) + 3));

    return 0;
}
```