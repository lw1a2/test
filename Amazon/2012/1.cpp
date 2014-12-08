#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getIntegerComplement(int n) {
    unsigned int tmp = 1;

    int nn = n;
    int count = 0;
    while (n)
    {
        ++count;
        n >>= 1;
    }

    for (int i = 0; i < count - 1; ++i)
    {
        tmp = (tmp << 1) | 1;
    }

    return tmp ^ nn;
}

//贪婪算法
//int minCoins(vector< int > a , int S) {
//    int j = 0;
//    for( int p = 1; p < a.size( ); ++p)
//    {
//        int tmp = a[ p ];
//        for( j = p; j > 0 && tmp > a[ j - 1 ]; j-- )
//            a[ j ] = a[ j - 1 ];
//        a[ j ] = tmp;
//    }
//
//    int count = 0;
//    while (S)
//    {
//        int p = 0;
//        for (; p < a.size( ); ++p )
//        {
//            if (S - a[p] >= 0)
//            {
//                S -= a[p];
//                ++count;
//                break;
//            }
//        }
//        if (p == a.size( )) return -1;
//    }
//
//    return count;
//}

//动态规划
int minCoins(vector< int > a , int S)
{
    const unsigned int MAX = 65535;   
    int j = 0;
    for( int p = 1; p < a.size(); ++p)
    {
        int tmp = a[ p ];
        for(j = p; j > 0 && tmp > a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }

    vector<int> cents;
    cents.push_back(0);
    for (int i = 1; i <= S; i++)
    {
        cents.push_back(MAX);
    }       

    for (int m = 1; m <= S; m++)
    {
        for (int i = 0; i < a.size(); i++)
        {
            if (m >= a[i])
            {
                int tmp = cents[m - a[i]] + 1;
                if (tmp < cents[m])
                {
                    cents[m] = tmp;
                }
            }
        }
    }

    if (cents[S] < MAX)
    {
        return cents[S];
    }
    else
    {
        return -1;
    }
}

void f1()
{
    cout << getIntegerComplement(50) << endl;
    cout << getIntegerComplement(100) << endl;
    cout << getIntegerComplement(100000) << endl;
}

void f2()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);

    cout << minCoins(a, 11) << endl;

    vector<int> b;
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);

    cout << minCoins(b, 11) << endl;

    vector<int> c;
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);

    cout << minCoins(c, 5) << endl;
}

int main()
{

    f1();

    

    return 0;
}
