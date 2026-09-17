/*
1、位操作置位与清零
定义一个宏 BIT_MASK(bit) 用于生成对应位的掩码。然后编写两个内联函数：
set_bit(int *reg, int n) //传递整数reg，将第n位置1
clear_bit(int *reg, int n) //传递整数reg，将第n位置0
不允许使用循环和 - 号，仅用位运算。
*/

#define BIT_MASK(bit) (1<<(bit))

set_bit(int *reg, int n){
    *reg = *reg | BIT_MASK(n);

}

clear_bit(int *reg, int n){
    *reg = *reg & ~BIT_MASK(n);
}