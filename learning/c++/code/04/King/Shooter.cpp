#include <iostream>
#include "Shooter.h"

using namespace std;

Shooter::Shooter(int range) : m_range(range)
{
    cout << "create Shooter" << endl;
}

void Shooter::GetRange()
{
    cout << "range value is: " << m_range << endl;
}
