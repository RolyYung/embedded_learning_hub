#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
    set<int> sArr;
    sArr.insert(50);
    sArr.insert(7);
    sArr.insert(20);
    sArr.insert(40);
    sArr.insert(30);

    set<int>::iterator it = sArr.upper_bound(20);
    if(it != sArr.end()){
        cout << "find it! " << *it << endl;
    }else{
        cout << "not found" << endl;
    }

    
    return 0;
}