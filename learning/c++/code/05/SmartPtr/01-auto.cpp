#include <iostream>
#include <memory>

using namespace std;

class Test
{
public:
    Test(const string &str = "hello world"): m_str(str)
    {
        cout << "create Test" << endl;
    }

    void Show() 
    {
        cout << m_str << endl;
    }

    ~Test(){
        cout << "release Test" << endl;
    }
private:
    string m_str;
};

void AutoPtr()
{
    auto_ptr<Test> ap(new Test[5]); // 不能管理数组
    auto_ptr<Test> ap2 = ap; // 拷贝是移动构造, 会清空前值.
    // ap->Show();
    // ap->Show();
}

void UniquePtr()
{
    unique_ptr<Test> ap(new Test);
    ap->Show();

    // unique_ptr<Test> ap2 = ap;
    // ap2->Show();

    unique_ptr<Test[]> ap3(new Test[5]);
    ap3[0].Show();
}

void SharedPtr()
{
    shared_ptr<Test> sp(new Test);
    sp->Show();

    shared_ptr<Test> sp2 = sp;
    sp2->Show();
}

int main(int argc, char *argv[])
{
    SharedPtr();
    
    return 0;
}