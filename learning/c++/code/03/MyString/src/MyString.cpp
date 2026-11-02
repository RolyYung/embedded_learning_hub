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
    if(number > 0){
        int length = 1;
        int num = 10;
        while (number >= num)
        {
            num *= 10;
            length++;
        }
        // 定义承接字符串
        char* buf = new char[length+1]{0};
        for (int i = length-1; i >= 0; i--)
        {
            buf[i] = '0' + number % 10;
            number /= 10;
        }
        buf[length] = '\0';
        MyString str{buf};
        delete []buf;
        return str;
    }else if(number < 0){
        int _number = -(number);
        int length = 1;
        int num = 10;
        while (_number >= num)
        {
            num *= 10;
            length++;
        }
        // 定义承接字符串
        char* buf = new char[length+2]{0};
        for (int i = length; i >= 1; i--)
        {
            buf[i] = '0' + _number % 10;
            _number /= 10;
        }
        buf[length+1] = '\0';
        buf[0] = '-';
        MyString str{buf};
        delete []buf;
        return str;
    }else{
        MyString str{"0"};
        return str;
    }
}