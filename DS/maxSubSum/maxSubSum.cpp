#include <iostream>
#include <vector>

using namespace std;

//���η�
int maxSubRec(const vector<int>& a, int left, int right)
{
    if (left == right)
    {
        if (a[left] > 0)
        {
            return a[left];
        }
        else
        {
            return 0;
        }
    }

    int mid = (left + right) / 2;

    //��벿�ֵ����ֵ
    int maxLeft = maxSubRec(a, left, mid);
    //�Ұ벿�ֵ����ֵ
    int maxRight = maxSubRec(a, mid + 1, right);
    
    //��Խ���Ҳ��ֵ����ֵ
    //��Խ���󲿷�
    int maxLeftSub = 0;
    int sumLeftSub = 0;
    for (int i = mid; i >= left; --i)
    {
        sumLeftSub += a[i];
        if (sumLeftSub > maxLeftSub)
        {
            maxLeftSub = sumLeftSub;
        }
    }
    //��Խ���Ҳ���
    int maxRightSub = 0;
    int sumRightSub = 0;
    for (int i = mid + 1; i <= right; ++i)
    {
        sumRightSub += a[i];
        if (sumRightSub > maxRightSub)
        {
            maxRightSub = sumRightSub;
        }
    }

    //������������
    return max(max(maxLeft, maxRight), maxLeftSub + maxRightSub);
}

int maxSubSum3(const vector<int>& a)
{
    return maxSubRec(a, 0, a.size() - 1);
}

//̰���㷨���������ʼλ��
int maxSubSum4(const vector<int>& a)
{
    int maxSum = 0, thisSum = 0;
    int maxBegin = 0, maxEnd = 0, thisBegin = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        thisSum += a[i];
        if (thisSum > maxSum)
        {
            maxSum = thisSum;
            maxBegin = thisBegin;
            maxEnd = i;
        }
        else if (thisSum < 0)
        {
            thisSum = 0;
            if (i + 1 < a.size())
            {
                thisBegin = i + 1;
            }
        }
    }

    cout << maxBegin << ".." << maxEnd << ": ";

    return maxSum;
}

//̰���㷨
int maxSubSum5(const vector<int>& a)
{
    int maxSum = 0;
    int tmp = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        tmp += a[i];
        if (maxSum < tmp)
        {
            maxSum = tmp;
        }
        else if (tmp < 0)
        {
            tmp = 0;
        }
    }

    return maxSum;
}

//����Сֵ
int minSubSum4(const vector<int>& a)
{
    int minSum = 0;
    int thisSum = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        thisSum += a[i];
        if (thisSum < minSum)
        {
            minSum = thisSum;
        }
        if (thisSum > 0)
        {
            thisSum = 0;
        }
    }

    return minSum;
}

int main()
{
    vector<int> a;
    a.push_back(4);
    a.push_back(-3);
    a.push_back(5);
    a.push_back(-2);
    a.push_back(-1);
    a.push_back(2);
    a.push_back(6);
    a.push_back(-2);

    cout << maxSubSum3(a) << endl;
    cout << maxSubSum4(a) << endl;
    cout << maxSubSum5(a) << endl;

    cout << minSubSum4(a) << endl;

    return 0;
}

