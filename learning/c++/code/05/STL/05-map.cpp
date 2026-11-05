#include <iostream>
#include <map>

using namespace std;

void MapTest()
{
    map<int, string> mArr{{1, "zhao"}, {2, "qian"}, {3, "sun"}};
    mArr.insert(map<int, string>::value_type(4, "li"));
    mArr.insert(pair<int, string>(5, "zhou"));

    map<int, string>::iterator it = mArr.begin();
    while (it != mArr.end())
    {
        cout << it->first << " => " << it->second << endl;
        it++;
    }
    
}

int main(int argc, char *argv[])
{
    MapTest();    
    return 0;
}