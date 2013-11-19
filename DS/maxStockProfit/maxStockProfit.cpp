#include <iostream>
#include <vector>

using namespace std;

//һ���еĶ���¼��㣬��Ʊ�в�ͬ�ļ�ֵ
//���ʱ���룬��ʱ������ʹ�������

//���η�
int maxStockProfit(const vector<int>& v, int left, int right)
{
    if (right - left >= 1)
    {
        int MAX = left;
        int MIN = left;

        //�ҵ���󣨹󣩵����С�����ˣ���
        for (int i = left; i <= right; ++i)
        {
            if (v[MAX] < v[i])
            {
                MAX = i;
            }
            if (v[MIN] > v[i])
            {
                MIN = i;
            }
        }

        if (MAX >= MIN)         //�����С�����֮ǰ����ֱ������С���룬�������
        {
            return v[MAX] - v[MIN];
        }
        else                    
        {
            //�����С�����֮����������֮ǰ����С��MIN2������С֮��ĵ����㣨MAX2��
            int MIN2 = left;
            for (int i = left + 1; i < MAX; ++i)
            {
                if (v[MIN2] > v[i])
                {
                    MIN2 = i;
                }
            }

            int MAX2 = 0;
            if (MIN + 1 <= right)
            {
                MAX2 = MIN + 1;
            }
            else
            {
                MAX2 = right;
            }
            for (int i = MIN + 2; i <= right; ++i)
            {
                if (v[MAX2] < v[i])
                {
                    MAX2 = i;
                }
            }
            //����v[MAX]-v[MIN2]��v[MAX2]-v[MIN]��maxStockProfit(v, MAX + 1, MIN - 1)
            //���ش��
            int profit3 = maxStockProfit(v, MAX + 1, MIN - 1);
            if (v[MAX] - v[MIN2] > v[MAX2] - v[MIN])
            {
                return max(v[MAX] - v[MIN2], profit3);
            }
            else
            {
                return max(v[MAX2] - v[MIN], profit3);
            }
        }

    }

    return 0;
}

//��ٷ�
int maxStockProfit2(const vector<int>& v, int left, int right)
{
    int MAX = 0;
    int buy = 0;
    int sell = 0;
    for (int i = left; i <= right - 1; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            if (MAX < v[j] - v[i])
            {
                MAX = v[j] - v[i];
                buy = i;
                sell = j;
            }
        }
    }

    cout << "buy(" << buy <<")-sell(" << sell << "): ";
    return MAX;
}

int maxStockProfit3(const vector<int>& v, int left, int right)
{
    int MIN = 0;
    int MAX = MIN + 1;
    int MIN2 = 0;

    for (int i = left; i <= right; ++i)
    {
        if (v[MAX] - v[MIN] < 0)
        {
            if (i + 1 > right)
            {
                MAX = right;
            }
            else
            {
                MAX = i + 1;
            }
            MIN = i;
        }
        else
        {
            if (v[MAX] < v[i])
            {
                MAX = i;
            }
            if (v[MIN] > v[i])
            {
                MIN2 = i;
            }
            if (v[MAX] - v[MIN] < v[i] - v[MIN2])
            {
                MIN = MIN2;
                MAX = i;
            }
        }
    }

    if (MAX > right)
    {
        MAX = right;
    }
    if (MIN == MAX)
    {
        MIN = MAX = 0;
    }

    cout << "buy(" << MIN <<")-sell(" << MAX << "): ";
    return v[MAX] - v[MIN];
}

int main()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(11);
    v.push_back(9);
    v.push_back(10);
    v.push_back(15);
    v.push_back(14);
    v.push_back(12);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(10);
    v.push_back(11);
    v.push_back(15);
    v.push_back(10);
    v.push_back(9);
    v.push_back(14);
    v.push_back(12);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(13);
    v.push_back(15);
    v.push_back(10);
    v.push_back(14);
    v.push_back(9);
    v.push_back(12);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    v.clear();
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(3);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << maxStockProfit(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit2(v, 0, v.size() - 1) << endl;
    cout << maxStockProfit3(v, 0, v.size() - 1) << endl;
    cout << endl;

    return 0;
}

