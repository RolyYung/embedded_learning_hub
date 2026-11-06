#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int sum = 0;
    int value = 0;

    while(cin >> value){
        sum += value;
    }

    cout << sum << endl;
    
    return 0;
}