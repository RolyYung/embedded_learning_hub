#include <iostream>
#include "MyString.h"

using namespace std;

int main(){
    // MyString string = "hello world";
    // string.Show();

    //operator code
    MyString s1{"hello "};
    MyString s2{" world"};
    MyString s3{s1+s2};
    s3.Show();
    s3 = s1;
    s3.Show();
    bool isEqual = (s1 == s3);
    if(isEqual){
        cout << "s1 == s3" << endl;
    }
    return 0;
}