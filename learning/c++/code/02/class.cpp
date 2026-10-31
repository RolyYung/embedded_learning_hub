#include <iostream>

using namespace std;

class Human 
{
// 成员属性
public: 

    void Eat(string food){
        cout << m_name + " is eating" + " " + food << endl;
    }

    void Sleep(){
        cout << m_name + " is sleeping" << endl;
    }

    void setName(const string &name){
        m_name = name;
        return;
    }

    void setAge(const int age){
        m_age = age;
        return;
    }

    string getName(){
        return m_name;
    }

    int getAge(){
        return m_age;
    }
private:
    // 成员属性
    int m_age;
    string m_name;

};
int main(){
    Human ZS;
    

    ZS.setAge(18);
    ZS.setName("roly");

    cout << ZS.getName() << endl;
    cout << ZS.getAge() << endl;

    
    ZS.Sleep();
    ZS.Eat("beef");
    
    cout << "hello world" << endl;
    return 0;
}