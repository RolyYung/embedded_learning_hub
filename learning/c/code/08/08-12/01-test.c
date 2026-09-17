/*
【规则 1-38】return 语句不可返回指向“栈内存”的“指针”，因为该内存在函数体结束时
被自动销毁。
*/

int* func(int *p){
    *p = 20;
    return p;
}
int main(){
    
    int a = 10;
    int *b = func(&a);
    return 0;
}