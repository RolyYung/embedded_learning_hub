#include <iostream>
#include "MyString.h"
#include <cstring>
#include <cstdint>

using namespace std;

MyString::MyString(const char * buf){
    if(buf == nullptr){
        m_data = new char[1];
        *m_data = '\0';
    }else{
        int length = strlen(buf);
        m_data = new char[length+1];
        strcpy(m_data, buf);
    }
}

MyString::MyString(const MyString &other)
{
    int length = strlen(other.m_data);
    m_data = new char[length + 1];
    strcpy(m_data, other.m_data);
}

MyString::MyString(MyString &&other) : m_data(other.m_data)
{
    other.m_data = nullptr;
}

MyString::~MyString(){
    delete []this->m_data;
}

void MyString::Show(){
    cout << m_data <<endl;
    return;
}

MyString MyString::ToNumber(int number){
    bool isNeg = number < 0;
    if(isNeg){
        number = -number;
    }
    char buf[15]{0};
    int i = 0;
    do{
        buf[i] = number % 10 + '0';
        number /= 10;
        i++;
    }while(number > 0);
    if(isNeg){
        buf[i++] = '-';
    }
    MyString str{buf};
    str.Reverse();
    
    return str;
}

void MyString::Reverse(){
    int length = strlen(this->m_data);
    for (int i = 0; i < length / 2; i++)
    {
        char temp = this->m_data[i];
        this->m_data[i] = this->m_data[length - 1 - i];
        this->m_data[length - 1 - i] = temp;
    }
    
}