# 数组和大小端题目

## 第 1 题：判断大小端

分别写出下面代码在大端和小端机器上的输出。

```c
uint32_t x = 0x12345678;
unsigned char *p = (unsigned char *)&x;

printf("%02X %02X\n",
       (unsigned int)p[0],
       (unsigned int)p[3]);
```

---

## 第 2 题：数组的内存排列

请分别写出大端和小端机器上，从 `a` 的起始地址开始，按地址从低到高排列的 6 个字节。

```c
uint16_t a[3] = {0x1234, 0x5678, 0x9ABC};
```

---

## 第 3 题：通过字节指针访问数组

分别写出大端和小端机器上的输出。

```c
uint32_t a[2] = {0x11223344, 0x55667788};
unsigned char *p = (unsigned char *)a;

printf("%02X %02X %02X\n",
       (unsigned int)p[1],
       (unsigned int)p[4],
       (unsigned int)p[6]);
```

---

## 第 4 题：修改数组中的一个字节

分别写出大端和小端机器上的输出。

```c
uint32_t a[2] = {0x12345678, 0xAABBCCDD};
unsigned char *p = (unsigned char *)a;

p[0] = 0xFF;
p[ ] = 0x00;

printf("%08X %08X\n",
       (unsigned long long)a[0],
       (unsigned long long)a[1]);
```

---

## 第 5 题

在小端和大端系统下，下面函数的值是多少？

```c
Int main()
{
    Int a[6] = {10, 8, 6, 4, 2, 0};

    Int *p1 = (int *)(&a + 1);
    Int *p2 = (int *)((int)a + 1);
    Int *p3 = (int *)((int)a + 3);

    Printf("%x, %x，%x", p1[-1], *p2, *p3);

    Return 0;
}
```

---

## 第 6 题

在小端和大端系统下，下面函数的值是多少？

### 格式说明

- `%`：格式说明开始
- `0`：不足宽度时用 `0` 补齐
- `8`：最小输出宽度为 8
- `x`：小写十六进制

```c
#include <stdio.h>

int main(void)
{
    unsigned int x = 0x12345678;
    unsigned char *p = (unsigned char *)&x;

    printf("%02x %02x %02x %02x\n",
           p[0], p[1], p[2], p[3]);

    unsigned int y = ((unsigned int)p[0] << 24) |
                     ((unsigned int)p[1] << 16) |
                     ((unsigned int)p[2] << 8)  |
                     p[3];

    printf("%08x\n", y);

    return 0;
}
```

---

## 第 7 题

分别写出大端和小端机器上的输出，并指出 `p[4]` 属于哪个数组元素。

```c
uint16_t a[2][2] = {
    {0x1122, 0x3344},
    {0x5566, 0x7788}
};

unsigned char *p = (unsigned char *)&a;

printf("%02X %02X\n",
       (unsigned int)p[4],
       (unsigned int)p[7]);

printf("%04X\n", (unsigned int)a[1][0]);
```