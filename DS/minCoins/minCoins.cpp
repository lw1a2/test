#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const unsigned int MAX = 65535000;

//贪婪算法
//int minCoins(vector<int> a , int S) {
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


//分析：
//假设对于i = 1...N-1，所需最少的硬币数minCoins(i)已知，
//那么对于N，所需的硬币数为min(minCoins(i) + minCoins(N-i))，其中i=1...N-1;
//递归实现
int minCoinsRec(vector<int> a, int S)
{
    if (0 == S)
    {
        return 0;
    }

    if (S < a[0])
    {
        return MAX;
    }

    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] == S)
        {
            return 1;
        }
    }

    int tmp = MAX;
    for (int i = 1; i < S; ++i)
    {
        tmp = min(tmp, minCoinsRec(a, i) + minCoinsRec(a, S - i));
    }

    return tmp;
}
int minCoins(vector<int> a, int S)
{
    sort(a.begin(), a.end());

    int tmp = minCoinsRec(a, S);

    if (MAX == tmp)
    {
        return -1;
    }

    return tmp;
}

//分析：
//假设对于i = 1...N-1，所需最少的硬币数minCoins(i)已知，
//那么对于N，所需的硬币数为min(minCoins(i) + minCoins(N-i))，其中i=1...N-1;
//动态规划
//时间复杂度：S^2
int minCoins2(vector<int> a , int S)
{
    vector<int> C(S + 1, MAX);
    C[0] = 0;

    //初始配置：一个硬币就能完成拼凑
    for (int i = 0; i < a.size(); ++i)
    {
        C[a[i]] = 1;
    }

    for (int j = 0; j <= S; ++j)
    {
        int MIN = MAX;
        for (int i = 0; i <= j / 2; ++i)
        {
            if (C[i] + C[j - i] < MIN)
            {
                MIN = C[i] + C[j - i];
            }
        }
        C[j] = MIN;
    }

    if (MAX == C[S])
    {
        return -1;
    }

    return C[S];
}

//动态规划（目前最优的）
//时间复杂度：S*a.size()
int minCoins3(vector<int> a , int S)
{
    vector<int> C(S + 1, MAX);
    C[0] = 0;

    //j代表要组装的钱的大小
    //C[j]表示要组装j的话，需要的硬币数
    for (int j = 0; j <= S; ++j)
    {
        for (int i = 0; i < a.size(); ++i)
        {
            //j大于等于硬币面值，说明可能被一个或多个硬币组装
            if (j >= a[i])
            {
                //C[j - a[i]]或为最小硬币数了，或为MAX
                //所以对于j，所需的最小硬币数为min(C[j - a[i]]) + 1，其中i=0..a.size()-1
                int tmp = C[j - a[i]] + 1;
                if (tmp < C[j])
                {
                    C[j] = tmp;
                }
            }
        }
    }

    if (C[S] < MAX)
    {
        return C[S];
    }
    else
    {
        return -1;
    }
}

int main()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    cout << minCoins(a, 11) << endl;
    cout << minCoins2(a, 11) << endl;
    cout << minCoins3(a, 11) << endl;
    cout << endl;
    cout << minCoins(a, 0) << endl;
    cout << minCoins2(a, 0) << endl;
    cout << minCoins3(a, 0) << endl;
    cout << endl;

    vector<int> b;
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);
    b.push_back(5);
    cout << minCoins(b, 11) << endl;
    cout << minCoins2(b, 11) << endl;
    cout << minCoins3(b, 11) << endl;
    cout << endl;

    vector<int> c;
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);
    cout << minCoins(c, 5) << endl;
    cout << minCoins2(c, 5) << endl;
    cout << minCoins3(c, 5) << endl;
    cout << endl;
    //cout << minCoins(c, 500000) << endl; //递归实现，时间太长了
    //cout << minCoins2(c, 500000) << endl;   //我的实现，时间次之
    cout << minCoins3(c, 500000) << endl;   //网上的实现，最优
    cout << endl;

    return 0;
}

