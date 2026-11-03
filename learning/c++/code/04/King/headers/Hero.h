#ifndef A84F8916_572A_4C07_B734_7FEB0E95F81C
#define A84F8916_572A_4C07_B734_7FEB0E95F81C

#include <iostream>

using namespace std;

class Hero
{
public:
    Hero(const string &id, int hp);
    ~Hero();

    void Skill();
    void Show() const;

private:
    string m_id;
    int m_hp;


};

#endif /* A84F8916_572A_4C07_B734_7FEB0E95F81C */
