#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Person
{
    string name;

    shared_ptr<Person> child;
    weak_ptr<Person> parent;

    Person(string n) : name(n)
    {}

    ~Person()
    {
        cout << name << "析构~" << endl;
    }

    void showParent()
    {
        if(auto p = parent.lock()){
            cout << "parent is : " << p->name << endl;
        }
        else{
            cout << "parent object is destroy" << endl;
        }
    }
};

int main(int argc, char *argv[])
{
    auto father = make_shared<Person>("父亲");
    auto child = make_shared<Person>("孩子");

    father->child = child;

    child->parent = father;

    cout << father.use_count() << endl;
    cout << child.use_count() << endl;
    
    child->showParent();

    father.reset();

    child->showParent();

    child.reset();
    
    return 0;
}