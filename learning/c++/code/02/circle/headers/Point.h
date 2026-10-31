#ifndef CB8C7A41_EEE9_4824_887A_B50F964E6DC9
#define CB8C7A41_EEE9_4824_887A_B50F964E6DC9

class Point{
public:
    Point(int x, int y);
    void SetX(int x);
    int GetX();

    void SetY(int y);
    int GetY();

    void Show();
private:
    int m_x;
    int m_y;
};

#endif /* CB8C7A41_EEE9_4824_887A_B50F964E6DC9 */
