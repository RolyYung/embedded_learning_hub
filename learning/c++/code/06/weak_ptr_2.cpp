#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Student
{
public:
    string name;

    Student(string n): name(n)
    {}

    ~Student()
    {
        cout << name << " destucted \n";
    }
};

class Teacher
{
public:
    weak_ptr<Student> stu;

    void showStudent()
    {
        auto s = stu.lock();
        if(s != nullptr){
            cout << "student name is : " << s->name << endl;
        }else{
            cout << "student is not exist" << endl;
        }
    }
};

int main()
{
    // Student s{"roly"};
    auto s = make_shared<Student>("roly");
    Teacher t;

    t.stu = s;
    t.showStudent();

    s.reset();

    t.showStudent();
    return 0;
}