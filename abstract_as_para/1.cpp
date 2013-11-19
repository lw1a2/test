class B
{
public:
	virtual ~B() = 0;
};

B::~B()
{
}

class D : public B
{
public:
};

void f(const B& b)
{
}

int main()
{
	B *p = new D;
	f(*p);
	D d;
	(B)d;
	return 0;
}

