#include <iostream>
#include <cstdlib>

using namespace std;

//当使用kill -9结束进程时，a的析构函数不能正常调用
class A
{
public:
    ~A()
    {
        cout << "~A()" << endl;
    }
};

A a;

int main()
{
    pause();
    return 0;
}

