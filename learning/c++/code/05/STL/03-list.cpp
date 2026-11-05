#include <iostream>
#include <list>

using namespace std;

void ListTest(){
    list<int> lArr;
    lArr.push_back(10);
    lArr.push_back(20);
    lArr.push_front(30);
    lArr.push_front(40);

    // for(int i : lArr){
    //     cout << i << " ";
    // }

    list<int>::iterator it = lArr.begin();
    while(it != lArr.end())
    {
        cout << *it++ << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    ListTest();
    
    return 0;
}