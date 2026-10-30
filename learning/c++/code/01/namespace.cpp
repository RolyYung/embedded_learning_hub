#include <cstdio>

namespace ZS{
    int a = 0;

    void Show(){
        printf("ZS \n");
    }
}

namespace LS {
    int a = 1;

    void Show(){
        printf("LS \n");
    }
}

// using namespace 

int a = 40;
using int32 = int;
int main(void){
    int32 a = 30;
    // using ZS::a;
    // using LS::Show;
    // printf("%d \n", ::a);
    printf("%d \n", a);
    // Show();

    return 0;
}