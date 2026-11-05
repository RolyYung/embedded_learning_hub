#include <iostream>
#include <vector>

using namespace std;

void VectorTest(){
    vector<int> vArr;
    int a = 10;
    vArr.push_back(a);
    vArr.push_back(a);
    vArr.push_back(a);
    vArr.push_back(a);

    vector<int>::iterator it = vArr.begin();
    
    while(it != vArr.end()){
        cout << *it << " ";
        it++;
    }
    cout << endl;

    vArr.clear();
    if(vArr.empty()){
        cout << "vArr is empty " << endl;
    }
    
}

int main(int argc, char *argv[])
{
    VectorTest();
    
    return 0;
}