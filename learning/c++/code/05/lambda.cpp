#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 5;
    
    auto p = [=]()mutable->int{
        a = 20;
        b=10;
        cout << a << endl;
        cout << b << endl;
        return a;
    };
    int c = p();
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    
    return 0;
}