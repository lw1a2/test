class B
{
private:
    ~B()
    {
    }
};

class D : public B
{
};

int main()
{
    B *p = new D;
    return 0;
}

