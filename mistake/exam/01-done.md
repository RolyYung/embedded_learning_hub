# 字符串数组题目

## 题目一

> 64 位系统

```c
int main(void)
{
    char *s1[] = {"abc", "defg", "hijk"};

    char s2[3][20] = {"abc", "defg", "hijk"};

    printf("A:sizeof = %u\n", (unsigned)sizeof(s1));

    printf("B:sizeof = %u\n", (unsigned)sizeof(s1[0]));

    printf("C:sizeof = %u\n", (unsigned)strlen(s1[0]));

    printf("D:sizeof = %u\n", (unsigned)sizeof(s2));

    //printf("C1:sizeof = %u\n", (unsigned)strlen(s2));

    printf("E:sizeof = %u\n", (unsigned)sizeof(s2[0]));

    printf("F:strlen = %u\n", (unsigned)strlen(s2[0]));

    return 0;
}
```

---

## 题目二

```C
void probe1(char str[])
{
    printf("C: sizeof=%u\n", (unsigned)sizeof(str));

    printf("D: strlen=%u\n", (unsigned)strlen(str));
}

void probe2(char *str)
{
    printf("E: sizeof=%u\n", (unsigned)sizeof(str));

    printf("F: strlen=%u\n", (unsigned)strlen(str));
}

int main()
{
    char s[3][20] = {"ab", "cd", "efg"};

    printf("A: sizeof=%u\n", (unsigned)sizeof(s[0]));

    printf("B: strlen=%u\n", (unsigned)strlen(s[0]));

    probe1(s[0]);

    probe2(s[0]);

    return 0;
}
```

### 类比 int 数组

```c
//void func2(int arr[])

void func2(int *ptr)
{
    printf("H:sizeof = %u\n", (unsigned)sizeof(ptr));
}

int main(void)
{
    int a[3][10];

    printf("G:sizeof = %u\n", (unsigned)sizeof(a[0]));

    func2(a[0]);

    return 0;
}
```

---

## 题目三

```c
#include <stdio.h>

void func(char **p);

int main(void)
{
    char *ch[] = {
        "apple", "banana", "cherry",
        "orange", "grape", "melon"
    };

    func(ch);

    return 0;
}

void func(char **p)
{
    char *ch;

    ch = (p += sizeof(short))[-2];

    printf("%s", ch + 2);
}
```

---

## 题目四

```c
void func1(char (*str)[20])

//void func1(char str[][20])

{
    printf("C:sizeof = %u\n", (unsigned)sizeof(str));

    //printf("D:strlen = %u\n", (unsigned)strlen(str));
}

void func2(char **s)
{
    printf("G:sizeof = %u\n", (unsigned)sizeof(s));

    //printf("D:strlen = %u\n", (unsigned)strlen(s));

    printf("H:strlen = %u\n", (unsigned)strlen(*s));
}

int main(void)
{
    char s[3][20] = {"ab", "cde", "fghi"};

    printf("A:sizeof = %u\n", (unsigned)sizeof(s));

    printf("B:strlen = %u\n", (unsigned)strlen(*s));

    //printf("B:strlen = %u\n", (unsigned)strlen(s));

    func1(s);

    char *s1[3] = {"ab", "cde", "fghi"};

    printf("E:sizeof = %u\n", (unsigned)sizeof(s1));

    printf("F:strlen = %u\n", (unsigned)strlen(*s1));

    func2(s1);

    return 0;
}
```