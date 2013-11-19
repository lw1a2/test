#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

/* 
��10�ڸ�������λ�� 
��λ�����壨��0��ʼ����������Ԫ�ظ���Ϊ����2n+1������λ��Ϊ��n������ 
                           ��Ԫ�ظ���Ϊż��2n������λ��Ϊ(��n-1����+��n����)/2
10�ڸ���������֯��������1�����ģ�⡣ 
1���������λ��Ϊ(v[4999]+v[5000])/2 
�����ڴ����ƣ�ÿ��ֻ��װ��100���� 
*/

const int NUM_IN_FILE = 10000;
const int MAX_ARRAY_NUM = 100;


long medianOfOneBillion()
{
    long MAX = 0;
    long tmp = 0;
    //��1��ѭ����q�ﱣ�����ǰ0..MAX_ARRAY_NUM��������0..99�����������99������ֵΪMAX
    //��2��ѭ����q�ﱣ����Ǵ���MAX��ǰ0..MAX_ARRAY_NUM������������
    //MAX_ARRAY_NUM+1..2*MAX_ARRAY_NUM��������100..199�����������199������ֵΪMAX
    //...
    //��50��ѭ����q�ﱣ���ǰ4900..4999
    //���4999�����ɵ�
    for (int j = 0; j < (NUM_IN_FILE / MAX_ARRAY_NUM) / 2; ++j)
    {
        priority_queue<long> q;
        //��MAX_ARRAY_NUM�����������ȼ�������
        ifstream f("input.txt");
        for (int i = 0; i < MAX_ARRAY_NUM;)
        {
            f >> tmp;
            if (tmp > MAX)
            {
                q.push(tmp);
                ++i;
            }
        }

        while (f >> tmp)
        {
            if (tmp < q.top() && tmp > MAX)
            {
                q.pop();
                q.push(tmp);
            }
        }
        
        MAX = q.top();
    }

    return MAX;
}

int main()
{
    ifstream f("input.txt");
    vector<long> v(NUM_IN_FILE);

    long tmp = 0;
    int i = 0;
    while (f)
    {
        f >> tmp;
        v[i++] = tmp;
    }

    sort(v.begin(), v.end());

    //������
    //cout << (v[4999] + v[5000]) / 2 << endl;
    cout << v[4999] << endl;

    //��ý��
    cout << medianOfOneBillion() << endl;

    return 0;
}

