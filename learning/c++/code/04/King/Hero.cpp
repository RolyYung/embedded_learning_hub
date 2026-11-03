#include <iostream>
#include "Hero.h"

using namespace std;

Hero::Hero(const string &id, int hp) : m_id(id), m_hp(hp)
{
    cout << "create Hero " << endl;
}

void Hero::Skill()
{
    cout << m_id << " use skill " << endl;
}

Hero::~Hero(){
    cout << "release Hero" << endl;
}

void Hero::Show() const{
    cout << "hp: " << m_hp << endl;
    cout << "id: " << m_id << endl; 
}