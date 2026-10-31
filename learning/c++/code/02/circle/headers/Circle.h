#ifndef C96C89BC_35CE_4579_9552_11BF78AE9B90
#define C96C89BC_35CE_4579_9552_11BF78AE9B90

#include "Point.h"
#include <iostream>

using namespace std;

class Circle
{

public: 
    Circle(int x, int y, int r);
    Circle(Point p, int r);
    void SetCenter(int x, int y);
    void SetRadius(int r);
    string pointAndCircle(Point p);

private: 
    int m_x;
    int m_y;
    int m_radius;
};

#endif /* C96C89BC_35CE_4579_9552_11BF78AE9B90 */
