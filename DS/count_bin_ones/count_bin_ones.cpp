#include <iostream>

using namespace std;

/*
    求整数的二进制表示中1的个数
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
    //k用来把左半部分“与”掉
    //例如k = 1111（二进制），n = 1100100（二进制）
    //与之后，right_n = 0100
    right_n = k & n;

    //左半部分
    int left = ones_divide_conquer(left_n, size);
    //右半部分
    int right = ones_divide_conquer(right_n, size);

    return left + right;
}

//分治法
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
        //如果最低位是1，则++count
        if (n & 1)
        {
            ++count;
        }
        //右移一位
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

