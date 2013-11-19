/*
公路收费点重建问题，详细见《数据结构与算法分析：C++描述（第3版）》P337
*/
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

const int INVALID = -1;

bool checkDist(const vector<int>& x, multiset<int>& d, multiset<int>& deleted_dist,
               int point, int left, int right)
{
    for (int i = left; i <= right; ++i)
    {
        if (x[i] != INVALID)
        {
            int dist = 0;   //point所产生的距离
            if (point > x[i])
            {
                dist = point - x[i];
            }
            else if(point < x[i])
            {
                dist = x[i] - point;
            }
            else            //不和自己比较
            {
                continue;
            }

            multiset<int>::iterator it = d.find(dist);
            if (it != d.end())
            {
                //如果距离在d中，则删除，并把删除的距离保存到已删set里
                d.erase(it);
                deleted_dist.insert(dist);
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool place(vector<int>& x, multiset<int>& d, int n, int left, int right)
{
    if (d.empty() || left > right)
    {
        return true;
    }
    
    int dmax = *(--d.end());

    //首先尝试x[right]=dmax
    x[right] = dmax;
    //把dmax删掉
    d.erase(d.find(dmax));
    multiset<int> deleted_dist;
    //检查距离在d里是否存在，由于从右侧插入，所以忽略和节点1之间的距离
    bool dist_exist = checkDist(x, d, deleted_dist, x[right], 2, x.size() - 1);

    bool right_ok = false;
    if (dist_exist)
    {
        //尝试从left到right-1填入
        right_ok = place(x, d, n, left, right - 1);
    }

    if (!dist_exist || !right_ok)
    {
        //如果x[right]不行，或者尝试从left到right-1填入失败，则首先恢复数据（回溯）
        x[right] = INVALID;
        for (multiset<int>::iterator it = deleted_dist.begin(); it != deleted_dist.end(); ++it)
        {
            d.insert(*it);
        }

        //尝试x[left]=x[n]-dmax
        x[left] = x[n] - dmax;
        //检查距离在d里是否存在，，由于从做侧插入，所以忽略和最后一个节点之间的距离
        dist_exist = checkDist(x, d, deleted_dist, x[left], 1, x.size() - 2);
    }

    bool left_ok = false;
    if (dist_exist)
    {
        //尝试从left+1到right填入
        left_ok = place(x, d, n, left + 1, right);
    }

    if (!dist_exist || !left_ok)
    {
        //如果x[left]不行，或者尝试从left + 1到right填入失败，则恢复数据（回溯）
        x[left] = INVALID;
        for (multiset<int>::iterator it = deleted_dist.begin(); it != deleted_dist.end(); ++it)
        {
            d.insert(*it);
        }
    }

    //如果从左侧插入失败，则把最开始删除的距离放回（回溯）
    if (!right_ok && !left_ok)
    {
        d.insert(dmax);
    }

    return left_ok;
}

bool turnpike(vector<int>& x, multiset<int>& d, int n)
{
    x[1] = 0;
    multiset<int>::iterator it = d.end();
    x[n] = *(--it);
    x[n - 1] = *(--it);
    d.erase(x[n]);
    d.erase(x[n - 1]);

    it = d.find(x[n] - x[n - 1]);
    if (it != d.end())
    {
        d.erase(it);
        return place(x, d, n, 2, n - 2);
    }
    else
    {
        return false;
    }
}

int main()
{
    multiset<int> d;
    d.insert(1);
    d.insert(2);
    d.insert(2);
    d.insert(2);
    d.insert(3);
    d.insert(3);
    d.insert(3);
    d.insert(4);
    d.insert(5);
    d.insert(5);
    d.insert(5);
    d.insert(6);
    d.insert(7);
    d.insert(8);
    d.insert(10);

    //一元二次方程求根，方程n(n-1)/2=d.size()
    int n = (1 + sqrt(1 + 8 * d.size())) / 2;
    vector<int> x(n + 1, INVALID);

    cout << turnpike(x, d, n) << endl;

    return 0;
}

