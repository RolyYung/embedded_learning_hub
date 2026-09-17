/*
给定一个简单的状态机场景：状态有 INIT, RUNNING, STOPPED。请定义一个函数指针数组 void (*state_func[])(void)，并用它代替 switch-case 实现状态跳转。说明这种表驱动法的优势。函数名自己取。
*/
enum State{
    INIT,
    RUNNING,
    STOPPED
};
void init(void){}
void running(void){}
void stopped(void){}
void (*state_func[])(void) = {init, running, stopped};
int main(){
    enum State state = INIT ;
    state_func[state];
    return 1;
}