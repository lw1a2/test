#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
从100万个数据中选出最小的100个 
此问题不适合用快速选择来做，因为100万个数放入内存，开销太大 
*/

void quickSort(vector<int>& v, int left, int right)
{
    if (left == right - 1)
    {
        if (v[left] > v[right])
        {
            swap(v[left], v[right]);
        }
        return;
    }

    if (left < right)
    {
        //选择枢纽元
        int center = (left + right) / 2;
        if (v[left] > v[center])
        {
            swap(v[left], v[center]);
        }
        if (v[left] > v[right])
        {
            swap(v[left], v[right]);
        }
        if (v[center] > v[right])
        {
            swap(v[center], v[right]);
        }

        //把枢纽元放到比较序列外
        swap(v[center], v[right - 1]);

        int i = left + 1;
        int j = right - 2;
        while (1)
        {
            while (v[i] < v[right - 1])
            {
                ++i;
            }
            while (v[j] > v[right - 1])
            {
                --j;
            }
            if (i < j)
            {
                swap(v[i], v[j]);
            }
            else
            {
                break;
            }
        }
        //把枢纽元放回比较序列
        swap(v[i], v[right - 1]);
        
        quickSort(v, left, i - 1);
        quickSort(v, i + 1, right);
    }
}



/*
方法一： 
选取前100个，放入一个数组中，并对其进行排序。 
遍历剩下的元素，如果元素小于数组的第100个，则删除第100个，把此元素插入到数组的正确位置上。 
*/
void f()
{
    const int N = 100;
    ifstream f("input.txt");
    vector<int> v(N);

    int tmp = 0;
    for (int i = 0; i < N; ++i)
    {
        f >> tmp;
        v[i] = tmp;
    }

    //对v进行快速排序
    quickSort(v, 0, v.size() - 1);

    for (int i = N + 1; i < 1000000; ++i)
    {
        f >> tmp;
        for (int j = 0; j < N; ++j)
        {
            if (v[j] > tmp)
            {
                for (int k = N - 1; k > j; --k)
                {
                    v[k] = v[k - 1];
                }
                v[j] = tmp;
                break;
            }
        }
    }

    ofstream f2("output.txt");
    for (int i = 0; i < N; ++i)
    {
        f2 << v[i] << '\n';
    }
}


void down(vector<int>& v, int x)
{
    int tmp = v[x];
    int child = x * 2 + 1;
    int j = x;
    while (child < v.size())
    {
        if (child + 1 < v.size() && v[child] < v[child + 1])
        {
            ++child;
        }
        if (tmp < v[child])
        {
            v[j] = v[child];
            j = child;
            child = child * 2 + 1;
        }
        else
        {
            break;
        }
    }
    v[j] = tmp;
}

/*
方法二： 
选取前100个，放入一个二叉堆中（大的在根上）。
遍历剩下的元素，如果元素小于数组的第1个，则删除第1个，把此元素插入到数组的正确位置上 
*/
void f2()
{
    const int N = 100;
    ifstream f("input.txt");
    vector<int> v(N);

    int tmp = 0;
    for (int i = 0; i < N; ++i)
    {
        f >> tmp;
        v[i] = tmp;
    }

    //buildHeap
    for (int i = v.size() / 2; i >= 0; --i)
    {
        down(v, i);
    }

    for (int i = N + 1; i < 1000000; ++i)
    {
        f >> tmp;
        if (tmp < v[0])
        {
            v[0] = tmp;
            down(v, 0);
        }
    }

    //quickSort(v, 0, v.size() - 1);

    ofstream f2("output2.txt");
    for (int i = 0; i < N; ++i)
    {
        f2 << v[i] << '\n';
    }
}


int main()
{
    f2();

    return 0;
}

