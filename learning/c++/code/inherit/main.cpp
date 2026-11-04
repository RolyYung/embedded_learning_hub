#include <iostream>

using namespace std;

class Animal
{
public: 
    string name;

    void eat()
    {
        cout << "animal is eating" << endl;
    }

    virtual void sound(){
        cout << "default sound" << endl;
    }

    // 函数声明
    ~Animal() = default;
};

class Cat : public Animal
{
public: 


    void catchMouse()
    {
        cout << "cat is catching mouse" << endl;
    }

    // void sound() override
    // {
    //     cout << "miao miao miao" << endl;
    // }
};


int main(int argc, char *argv[])
{
    Cat cat;
    cat.name = "xiao hua";
    
    cat.eat();
    cat.sound();
    
    return 0;
}