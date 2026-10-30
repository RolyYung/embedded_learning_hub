#include <iostream>

using namespace std; 

int main(){
    int *a = new int();
    
    cout << *a << endl;
    delete a;
    a = nullptr;

    int *arr = new int[5]{1,2,3,4,5};
    cout << arr[1] << endl;
    delete []arr;
    arr = nullptr;

    return 0;
}