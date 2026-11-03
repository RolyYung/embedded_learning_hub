#ifndef D95EF606_1669_4A83_991F_282C35E1FF43
#define D95EF606_1669_4A83_991F_282C35E1FF43
#include <iostream>
#include "Hero.h"
#include "Shooter.h"

class LuBan : public Hero, public Shooter
{
public: 
    LuBan(const string &id);
    ~LuBan();

    void Show();
    void Skill();

private: 
    int m_leglen;
};
#endif /* D95EF606_1669_4A83_991F_282C35E1FF43 */
