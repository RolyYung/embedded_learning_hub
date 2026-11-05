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
    vArr.pop_back();
    vArr.pop_back();

    for (size_t i = 0; i < vArr.size(); i++)
    {
        /* code */
        cout << vArr[i] << " ";
        cout << vArr.at(i) << " ";
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