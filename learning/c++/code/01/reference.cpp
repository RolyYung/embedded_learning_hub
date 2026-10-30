#include <iostream>

using namespace std;

void show(int &a, int &b){
    cout << a << ' ' << b << endl;
    return ;
}

int main(){

    int a = 10;
    int b = 30;

    cout << a << ' ' << b << endl;

    
    int &q = a; // 定义一个左值引用.
    show(a, b);

    return 0;
}