//�麯���Ļ�����

class B
{
public:
    virtual void f()
    {
    }
};

class D : public B
{
public:
    virtual void f()
    {
    }
};

int main()
{
    B* p = new D;
    p->f();

    return 0;
}

