#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const unsigned int MAX = 65535000;

//̰���㷨
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


//������
//�������i = 1...N-1���������ٵ�Ӳ����minCoins(i)��֪��
//��ô����N�������Ӳ����Ϊmin(minCoins(i) + minCoins(N-i))������i=1...N-1;
//�ݹ�ʵ��
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

//������
//�������i = 1...N-1���������ٵ�Ӳ����minCoins(i)��֪��
//��ô����N�������Ӳ����Ϊmin(minCoins(i) + minCoins(N-i))������i=1...N-1;
//��̬�滮
//ʱ�临�Ӷȣ�S^2
int minCoins2(vector<int> a , int S)
{
    vector<int> C(S + 1, MAX);
    C[0] = 0;

    //��ʼ���ã�һ��Ӳ�Ҿ������ƴ��
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

//��̬�滮��Ŀǰ���ŵģ�
//ʱ�临�Ӷȣ�S*a.size()
int minCoins3(vector<int> a , int S)
{
    vector<int> C(S + 1, MAX);
    C[0] = 0;

    //j����Ҫ��װ��Ǯ�Ĵ�С
    //C[j]��ʾҪ��װj�Ļ�����Ҫ��Ӳ����
    for (int j = 0; j <= S; ++j)
    {
        for (int i = 0; i < a.size(); ++i)
        {
            //j���ڵ���Ӳ����ֵ��˵�����ܱ�һ������Ӳ����װ
            if (j >= a[i])
            {
                //C[j - a[i]]��Ϊ��СӲ�����ˣ���ΪMAX
                //���Զ���j���������СӲ����Ϊmin(C[j - a[i]]) + 1������i=0..a.size()-1
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
    //cout << minCoins(c, 500000) << endl; //�ݹ�ʵ�֣�ʱ��̫����
    //cout << minCoins2(c, 500000) << endl;   //�ҵ�ʵ�֣�ʱ���֮
    cout << minCoins3(c, 500000) << endl;   //���ϵ�ʵ�֣�����
    cout << endl;

    return 0;
}

