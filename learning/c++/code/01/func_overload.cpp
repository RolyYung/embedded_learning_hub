#include <iostream>

using namespace std;

void Show(int i){
    cout << i << endl;
    return ;
}

void Show(char i){
    cout << i << endl;
    return ;
}

void Show(int i, int j){
    cout << i << endl;
    cout << j << endl;
    return ;
}

int main(){
    Show(10);
    Show('a');
    Show(10, 20);

    return 0;
}