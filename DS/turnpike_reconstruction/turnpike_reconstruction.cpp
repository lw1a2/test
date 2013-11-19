/*
��·�շѵ��ؽ����⣬��ϸ�������ݽṹ���㷨������C++��������3�棩��P337
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
            int dist = 0;   //point�������ľ���
            if (point > x[i])
            {
                dist = point - x[i];
            }
            else if(point < x[i])
            {
                dist = x[i] - point;
            }
            else            //�����Լ��Ƚ�
            {
                continue;
            }

            multiset<int>::iterator it = d.find(dist);
            if (it != d.end())
            {
                //���������d�У���ɾ��������ɾ���ľ��뱣�浽��ɾset��
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

    //���ȳ���x[right]=dmax
    x[right] = dmax;
    //��dmaxɾ��
    d.erase(d.find(dmax));
    multiset<int> deleted_dist;
    //��������d���Ƿ���ڣ����ڴ��Ҳ���룬���Ժ��Ժͽڵ�1֮��ľ���
    bool dist_exist = checkDist(x, d, deleted_dist, x[right], 2, x.size() - 1);

    bool right_ok = false;
    if (dist_exist)
    {
        //���Դ�left��right-1����
        right_ok = place(x, d, n, left, right - 1);
    }

    if (!dist_exist || !right_ok)
    {
        //���x[right]���У����߳��Դ�left��right-1����ʧ�ܣ������Ȼָ����ݣ����ݣ�
        x[right] = INVALID;
        for (multiset<int>::iterator it = deleted_dist.begin(); it != deleted_dist.end(); ++it)
        {
            d.insert(*it);
        }

        //����x[left]=x[n]-dmax
        x[left] = x[n] - dmax;
        //��������d���Ƿ���ڣ������ڴ�������룬���Ժ��Ժ����һ���ڵ�֮��ľ���
        dist_exist = checkDist(x, d, deleted_dist, x[left], 1, x.size() - 2);
    }

    bool left_ok = false;
    if (dist_exist)
    {
        //���Դ�left+1��right����
        left_ok = place(x, d, n, left + 1, right);
    }

    if (!dist_exist || !left_ok)
    {
        //���x[left]���У����߳��Դ�left + 1��right����ʧ�ܣ���ָ����ݣ����ݣ�
        x[left] = INVALID;
        for (multiset<int>::iterator it = deleted_dist.begin(); it != deleted_dist.end(); ++it)
        {
            d.insert(*it);
        }
    }

    //�����������ʧ�ܣ�����ʼɾ���ľ���Żأ����ݣ�
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

    //һԪ���η������������n(n-1)/2=d.size()
    int n = (1 + sqrt(1 + 8 * d.size())) / 2;
    vector<int> x(n + 1, INVALID);

    cout << turnpike(x, d, n) << endl;

    return 0;
}

