#include <iostream>
#include "Point.h"
#include "Circle.h"

using namespace std;

int main(int argc, char *argv[])
{
    Point p{10,20};
    
    Circle c{30, 20};
    c.SetRadius(10);

    cout << c.pointAndCircle(p) << endl;
    
    return 0;
}