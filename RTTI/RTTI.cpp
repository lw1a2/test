#include <iostream>
#include <typeinfo>

using namespace std;

class B
{
public:
    virtual ~B()
    {
    }
};

class D : public B
{
};

int main()
{
    B* p = new D;
    cout << dynamic_cast<D*>(p) << endl;    //NOT NULL
    cout << dynamic_cast<B*>(p) << endl;    //NOT NULL
    cout << typeid(*p).name() << endl;
    cout << typeid(p).name() << endl;       //����ָ��û��ʲô����
    p = new B;
    cout << dynamic_cast<D*>(p) << endl;    //NULL
    cout << dynamic_cast<B*>(p) << endl;    //NOT NULL
    cout << typeid(*p).name() << endl;
    cout << typeid(p).name() << endl;       //����ָ��û��ʲô����
    try
    {
        dynamic_cast<D&>(*p);
    }
    catch (bad_cast& e)
    {
        cout << "ERROR" << endl;
    }
    return 0;
}

