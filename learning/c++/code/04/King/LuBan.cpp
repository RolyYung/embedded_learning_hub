#include <iostream>
#include "LuBan.h"

using namespace std;

LuBan::LuBan(const string &id): Hero(id, 100), Shooter(500), m_leglen(50)
{
    cout << "create LuBan " << endl;
}

void LuBan::Show()
{
    Hero::Show();
    cout << "leglen: " << m_leglen << endl;
    Shooter::GetRange();
}

void LuBan::Skill()
{
    cout << "1 skill " << endl;
}

LuBan::~LuBan()
{
    cout << "release LuBan" << endl;
}