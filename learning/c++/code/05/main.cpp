#include <iostream>

using namespace std;

template <typename T>
void Show(T a, T b){
    cout << a << endl;
    cout << b << endl;
}

template <typename T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
    cout << a << " " << b << endl;
    return;
}

int main(int argc, char *argv[])
{
    Show<int>(10, 30);
    
    int a = 10;
    int b = 30;
    Swap<int>(a,b);
    
    return 0;
}