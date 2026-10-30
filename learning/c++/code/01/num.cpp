/*
    猜数字游戏
*/
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main(){
    srand(time(NULL));
    int a  = rand() % 100 + 1;
    int b;
    cout << a << endl;
    while (1)
    {
        cin >> b;

        if(cin.fail()){
            cout << "intpu error value" << endl;
            break;
        }
        if(a == b){
            cout << "successful!! rand num is: " << a << endl;
            return 0;
        }else{
            cout << "input num is not equal, try again" << endl;
        }
    }
    return 0;
}