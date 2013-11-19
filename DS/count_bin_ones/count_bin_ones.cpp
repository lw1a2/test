#include <iostream>

using namespace std;

/*
    �������Ķ����Ʊ�ʾ��1�ĸ���
*/

int ones(int n)
{
    //This my first solution:
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else if (n % 2 == 1) return ones(n / 2) + 1;
    else return ones(n / 2);

    //Answer from book:
    //  if (n < 2) return n;
    //  else return ones(n / 2) + n % 2;
}

int ones_divide_conquer(int n, int size)
{
    size = (size + 1) / 2;
    if (n < 2)
    {
        return n;
    }

    int left_n = n;
    int right_n = n;
    int k = 1;
    for (int i = 0; i < size; ++i)
    {
        left_n >>= 1;
        k <<= 1;
        k |= 1;
    }
    k >>= 1;
    //k��������벿�֡��롱��
    //����k = 1111�������ƣ���n = 1100100�������ƣ�
    //��֮��right_n = 0100
    right_n = k & n;

    //��벿��
    int left = ones_divide_conquer(left_n, size);
    //�Ұ벿��
    int right = ones_divide_conquer(right_n, size);

    return left + right;
}

//���η�
int ones2(int n)
{
    int count = 0;
    int tmp = n;
    while (tmp)
    {
        ++count;
        tmp >>= 1;
    }

    return ones_divide_conquer(n, count);
}


int ones3(int n)
{
    int count = 0;
    while (n)
    {
        //������λ��1����++count
        if (n & 1)
        {
            ++count;
        }
        //����һλ
        n >>= 1;
    }

    return count;
}

int main()
{
    cout << ones(100) << endl;
    cout << ones2(100) << endl;
    cout << ones3(100) << endl;

    return 0;
}

