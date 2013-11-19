#include <vector>
#include <iostream>
#include <exception>

using namespace std;

void insert(vector<int>& v, int x)
{
    v.push_back(x);
    int i = v.size() - 1;
    for (; i > 1 && x < v[i / 2]; i /= 2)
    {
        if (x < v[i / 2])
        {
            v[i] = v[i / 2];
        }
    }
    v[i] = x;
}

void percolateDown(vector<int>& v, int i)
{
    int tmp = v[i];
    int child = i;
    while (child * 2 + 1 < v.size())
    {
        child = child * 2 + 1;
        if (child + 1 < v.size() && v[child] > v[child + 1])
        {
            ++child;
        }
        if (tmp > v[child])
        {
            v[i] = v[child];
            i = child;
        }
        else
        {
            break;
        }
    }
    v[i] = tmp;
}

void deleteMin(vector<int>& v, int& x)
{
    if (v.size() <= 1)
    {
        throw exception();
    }
    x = v[1];
    v[1] = *(v.end() - 1);
    v.erase(v.end() - 1);
    percolateDown(v, 1);
}

void buildHeap(vector<int>& v)
{
    for (int i = v.size() / 2; i >= 0; --i)
    {
        percolateDown(v, i);
    }
}

int main()
{
    //使用插入来构造二叉堆
    vector<int> v;
    v.push_back(0);
    insert(v, 32);
    insert(v, 26);
    insert(v, 16);
    insert(v, 67);
    insert(v, 19);
    insert(v, 65);
    insert(v, 24);
    insert(v, 31);
    insert(v, 21);
    insert(v, 13);

    for (int i = 1; i <= 10; ++i)
    {
        cout << v[i] << endl;
    }

    cout << endl;

//  for (int i = 0; i < 10; ++i)
//  {
//      int x = 0;
//      deleteMin(v, x);
//      cout << x << endl;
//  }


    //使用下滤来构造二叉堆
    vector<int> v2;
    v2.push_back(32);
    v2.push_back(26);
    v2.push_back(16);
    v2.push_back(67);
    v2.push_back(19);
    v2.push_back(65);
    v2.push_back(24);
    v2.push_back(31);
    v2.push_back(21);
    v2.push_back(13);

    buildHeap(v2);
    for (int i = 0; i < 10; ++i)
    {
        cout << v2[i] << endl;
    }

    cout << endl;


    return 0;
}

