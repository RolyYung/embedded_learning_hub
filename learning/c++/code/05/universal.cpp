#include <iostream>

using namespace std;

template <typename T>
void TempShow(T &&i)
{
    i = 33;
    cout << "T && = " << i << endl;
}

int main(int argc, char *argv[])
{
    int a = 10;
    TempShow(a);
    TempShow(20);
    cout << a << endl;
    
    return 0;
}