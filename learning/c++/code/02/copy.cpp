#include <iostream>

using namespace std;

class A{
public:
    A(int i = 10, int j = 20) : i(i), j(new int(j))
    {

    }

    A(A&& other) : i(other.i), j(other.j)
    {
        cout << "move A" << endl;
        other.j = nullptr;
    }
    
    ~A(){
        cout << "release A" << endl;
        delete j;
    }

    int i;
    int *j;
};

A GetA(){
    A a;
    return a;
}

int main(){
    A a = GetA();


    return 0;
}