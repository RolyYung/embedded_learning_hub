#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y){
    m_x = x;
    m_y = y;
}

Point::Point(const Point &other){
    cout << "copy Point" << endl;
    m_x = other.m_x;
    m_y = other.m_y;
}

void Point::SetX(int x){
    m_x = x;
    return;
}

int Point::GetX(){
    return m_x;
}

void Point::SetY(int y){
    m_y = y;
    return;
}

int Point::GetY(){
    return m_y;
}

void Point::Show(){
    cout << GetX() << " " << GetY() << endl;
}

const Point Point::operator+(const Point &other) const
{
    int x = this->m_x + other.m_x;
    int y = this->m_y + other.m_y;
    return Point(x, y);
}

Point &Point::operator++(){
    ++m_x;
    ++m_y;
    return *this;
}

const Point Point::operator++(int){
    Point temp(*this);
    ++m_x;
    ++m_y;
    return temp;
}