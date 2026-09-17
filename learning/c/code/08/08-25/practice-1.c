/*
    设计一个函数，功能为将一个字符串逆序转换为数字输出
功能：传递一个数字字符串，将其反转后以int形式输出

例如：
输入："13579"   （char *类型）
输出：97531      （int类型）

要求：
1、考虑负数问题
    输入"-12345"  输出 -54321
2、考虑输入不合规问题
    输入 "123abc"     输出 格式不正确报错
3、考虑int越界问题
    输入"012345678999"      输出 数据越界报错

*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int reverse_str_to_num(char * str){
    int strLen = strlen(str);
    int result = 0;
    // 正数情况
    if(str[0] != '-'){
        if(strLen >= 10 ){
            printf("数字越界");
            return -1;
        }
        for (int i = strLen - 1; i >= 0; --i)
        {
            if(isalpha(str[i])){
                printf("格式不正确");
                return -1;
            }
            result += (str[i] - '0') * (int)pow(10, i);
        }
    }else{
        if(strLen-1 >= 10 ){
            printf("数字越界");
            return -1;
        }
        for (int i = strLen - 1; i > 0; --i)
        {
            if(isalpha(str[i])){
                printf("格式不正确");
                return -1;
            }
            result += (str[i] - '0') * (int)pow(10, i-1);
        }
        result *= -1;
    }
    return result;
}

int main(){
    char str[10];
    printf("输入字符串: ");
    scanf("%s", str);
    int result = reverse_str_to_num(str);
    if(result == -1){
        return -1;
    }
    printf("result: %d", result);
    return 0;
}