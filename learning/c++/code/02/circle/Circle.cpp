#include "Circle.h"
#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

Circle::Circle(int x, int y, int r): m_x(x), m_y(y)
{
    SetRadius(r);
}

Circle::Circle(Point p, int r): Circle(p.GetX(), p.GetY(), r)
{
}

void Circle::SetRadius(int r)
{
    m_radius = r;
    return;
}

string Circle::pointAndCircle(Point p){
    // 两点之间的距离 与 半径作比较
    // 大于就在圆外 小于在圆内 等于在圆上
    int p_x = p.GetX();
    int p_y = p.GetY();
    int c_x = m_x;
    int c_y = m_y;

    double x = fabs(p_x - c_x);
    double y = fabs(p_y - c_y);

    double distance = sqrt(pow(x, 2) + pow(y, 2));
    if(m_radius == (int)distance){
        return "on circle";
    }else if(m_radius > (int)distance){
        return "in circle";
    }else {
        return "out circle";
    }
    
}

