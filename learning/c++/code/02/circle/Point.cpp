#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(int x, int y){
    m_x = x;
    m_y = y;
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
