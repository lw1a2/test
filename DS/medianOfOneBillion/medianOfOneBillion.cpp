#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

/* 
求10亿个数的中位数 
中位数定义（以0开始计数）：若元素个数为奇数2n+1，则中位数为第n个数； 
                           若元素个数为偶数2n，则中位数为(第n-1个数+第n个数)/2
10亿个数不好组织，这里用1万个数模拟。 
1万个数的中位数为(v[4999]+v[5000])/2 
假设内存限制，每次只能装入100个数 
*/

const int NUM_IN_FILE = 10000;
const int MAX_ARRAY_NUM = 100;


long medianOfOneBillion()
{
    long MAX = 0;
    long tmp = 0;
    //第1次循环，q里保存的是前0..MAX_ARRAY_NUM个数（即0..99），并保存第99个数的值为MAX
    //第2次循环，q里保存的是大于MAX的前0..MAX_ARRAY_NUM个数，所以是
    //MAX_ARRAY_NUM+1..2*MAX_ARRAY_NUM个数（即100..199），并保存第199个数的值为MAX
    //...
    //第50次循环，q里保存的前4900..4999
    //则第4999个数可得
    for (int j = 0; j < (NUM_IN_FILE / MAX_ARRAY_NUM) / 2; ++j)
    {
        priority_queue<long> q;
        //将MAX_ARRAY_NUM个数放入优先级队列里
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

    //待求结果
    //cout << (v[4999] + v[5000]) / 2 << endl;
    cout << v[4999] << endl;

    //求得结果
    cout << medianOfOneBillion() << endl;

    return 0;
}

