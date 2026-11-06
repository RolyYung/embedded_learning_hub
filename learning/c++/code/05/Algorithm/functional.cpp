#include <iostream>
#include <functional>

using namespace std;

void Show(int i){
    cout << i << endl;
}

int main(int argc, char *argv[])
{
    function<void (int)> func = Show;
    func(10);
    
    return 0;
}