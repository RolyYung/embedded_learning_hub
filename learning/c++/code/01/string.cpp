#include <iostream>

using namespace std;

int main(){
    string str = "hello";
    string str2("world");
    string str3{"roly"};

    cout << str << endl;
    cout << str2 << endl;
    cout << str3 << endl;

    for (size_t i = 0; i < str.size();  i++)
    {
        cout << str[i] << endl;
    }

    str.clear();
    if(str.empty()){
        cout << "str is empty" << endl;
        cout << str << endl;
    }
    

    return 0;
}