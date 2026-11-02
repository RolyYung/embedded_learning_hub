#ifndef D2A08247_DF24_44A8_8800_900587CA41A6
#define D2A08247_DF24_44A8_8800_900587CA41A6

class MyString
{
private:
    /* data */
    char * m_data;
public:
    MyString(const char * buf = nullptr);
    MyString(const MyString &other);
    MyString(MyString &&other);
    ~MyString();

    static MyString ToNumber(int number);

    void Show();
};


#endif /* D2A08247_DF24_44A8_8800_900587CA41A6 */
