class B
{
public:
	void f(){}

protected:
	void f2(){}

private:
	void f3(){}
};

class D : protected B
{
public:
	void f4()
	{
		f2();
		//f3();
	}
};

int main()
{
	D d;
	d.f();
	//d.f2();
	//d.f3();
	d.f4();

	return 0;
}

