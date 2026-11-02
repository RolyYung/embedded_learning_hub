#include <iostream>
#include "Point.h"
#include "Circle.h"

using namespace std;

Point GetPoint(){
    Point p{20,30};
    return p;
}

int main(int argc, char *argv[])
{
    Point p{10,20};

    Point p2 = GetPoint();
    
    // Circle c{30, 20, 10};

    // cout << c.pointAndCircle(p) << endl;
    
    return 0;
}