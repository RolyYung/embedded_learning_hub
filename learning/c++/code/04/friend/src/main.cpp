#include <iostream>

using namespace std;

class Control;

class TV
{
public:
    TV(int channel = 1) : m_channel(channel)
    {}

    void show()
    {
        cout << "tv is watching " << m_channel << endl;
    }

    void ChangeC(Control &con);

    friend class Control;

private:
    int m_channel;

};



class Control
{
public:
    void ChangeChannel(int channel, TV &tv){
        tv.m_channel = channel;
        return;
    }

    friend class TV;
private:
    int i;
};

class Human
{
public:
    Human(int id): id(id) 
    {}
    
    friend void GetId(const Human &h);
private:
    int id;
};

void GetId(const Human &h){
    cout << "id is " << h.id << endl;
    return;
}

void TV::ChangeC(Control &con){
    con.i = 20;
}

int main(int argc, char *argv[])
{
    // Human h{430521};
    // GetId(h);
    TV tv;
    tv.show();
    Control con;
    con.ChangeChannel(5, tv);
    tv.show();
    tv.ChangeC(con);
    cout << "hello world " << endl;
    
    return 0;
}