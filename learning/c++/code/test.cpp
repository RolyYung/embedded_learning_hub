/*
“四支老鼠抬花轿，一支老鼠放鞭炮，前面两只当鼓手，咚隆咚隆真热闹，这时老猫来贺喜，一只一只全吃掉。”。这首儿歌描述了老鼠婚嫁的场面。完成下面两个问题：
（1） 就这段描述，找出所有可能对象，用C++定义相应的类，用文字说明各成员数据和函数的作用，不需给出成员函数的实现。
（2） 在main函数中，用你定义的类产生对象，并用这些对象尽可能地模拟出儿歌中描述的场面
*/
#include <iostream>

using namespace std;
class Mouse
{
public:
    Mouse(int in_num);
    void tai_hua_jiao()
    {
        cout << "抬花轿" << endl;
    }
    void da_gu()
    {
        cout << "打鼓" << endl;
    }

    void fang_bian_pao()
    {
        cout << "放鞭炮" << endl;
    }

private:
    int num;
};

class Cat
{
public: 
    Cat(int in_num): num(in_num){

    }
    void eating(int num)
    {
        cout << "eating mouse" << endl;
    }
private:
    int num;
};
Mouse::Mouse(int in_num) : num(in_num)
{

}

int main()
{
    Mouse mouse1{1};
    Mouse mouse2{2};
    Mouse mouse3{3};
    Mouse mouse4{4};
    mouse1.tai_hua_jiao();
    mouse2.tai_hua_jiao();
    mouse3.tai_hua_jiao();
    mouse4.tai_hua_jiao();
    Mouse mouse5{5};
    mouse5.fang_bian_pao();
    Mouse mouse6{6};
    mouse6.da_gu();

    Cat cat(1);
    cat.eating(1);
    cat.eating(2);
    cat.eating(3);
    cat.eating(4);
    cat.eating(5);
    cat.eating(6);
    return 0;
}