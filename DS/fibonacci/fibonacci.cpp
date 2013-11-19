#include <iostream>

using namespace std;

//�ݹ�ʵ��
long fib(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

//��̬�滮ʵ��
long fibonacci(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    long f_n_2 = 1;
    long f_n_1 = 1;
    long f_n = 1;

    for (int i = 2; i <= n; ++i)
    {
        //f(n)=f(n-1)+f(n-2)
        f_n = f_n_1 + f_n_2;
        //ǰ��һλ��
        //f(n-2)=f(n-1)
        f_n_2 = f_n_1;
        //f(n-1)=f(n)
        f_n_1 = f_n;
    }

    return f_n;
}

int main()
{
    cout << fib(40) << endl;
    cout << fibonacci(40) << endl;

    return 0;
}

