#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Show(int i)
{
    cout << i << " ";
    return ;
}

void AlgorithmTest()
{
    vector<int> vArr{10,20,3,4,6,1,2};
    for_each(vArr.begin(), vArr.end(), Show);

    cout << endl;

    int arr[10]{1,2,3,4,5,6,7,8,9,10};
    for_each(arr, arr+10, Show);
}

int main(int argc, char *argv[])
{
    AlgorithmTest();
    
    return 0;
}