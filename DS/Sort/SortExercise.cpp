#include <iostream>
#include <vector>

using namespace std;

/*
第7章 排序 
的习题 
*/

void e7_1()
{
    vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(1);
    v.push_back(5);
    v.push_back(9);
    v.push_back(2);
    v.push_back(6);
    v.push_back(5);

    for (int i = 1; i < v.size(); ++i)
    {
        int j = 0;
        int tmp = v[i];
        for (j = i; j > 0; --j)
        {
            if (v[j - 1] > tmp)
            {
                v[j] = v[j - 1];
            }
            else
            {
                break;
            }
        }
        v[j] = tmp;
    }

    cout << "Exercise 7.1:" << endl;
    for (int i = 0;  i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}


void e7_4()
{
    vector<int> v;
    v.push_back(9);
    v.push_back(8);
    v.push_back(7);
    v.push_back(6);
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);

    vector<int> gaps;
    gaps.push_back(1);
    gaps.push_back(3);
    gaps.push_back(7);

    for (int i = gaps.size() - 1; i >= 0; --i)
    {
        for (int j = gaps[i]; j < v.size(); j += gaps[i])
        {
            int k = 0;
            int tmp = v[j];
            for (k = j; k - gaps[i] >= 0; k -= gaps[i])
            {
                if (v[k - gaps[i]] > tmp)
                {
                    v[k] = v[k - gaps[i]];
                }
                else
                {
                    break;
                }
            }
            v[k] = tmp;
        }
    }

    cout << "Exercise 7.4:" << endl;
    for (int i = 0;  i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}

void down(vector<int>& v, int size, int x)
{
    //对于v[n]，父：v[(n-1)/2]，子：v[2n+1], v[2n+2]
    int tmp = v[x];
    int child = 2 * x + 1;
    int j = x;
    while (child < size)
    {
        if (child + 1 < size && v[child + 1] > v[child])
        {
            ++child;
        }
        if (tmp < v[child])
        {
            v[j] = v[child];
            j = child;
            child = 2 * child + 1;
        }
        else
        {
            break;
        }
    }
    v[j] = tmp;
}

void e7_11()
{
    vector<int> v;
    v.push_back(142);
    v.push_back(543);
    v.push_back(123);
    v.push_back(65);
    v.push_back(453);
    v.push_back(879);
    v.push_back(572);
    v.push_back(434);
    v.push_back(111);
    v.push_back(242);
    v.push_back(811);
    v.push_back(102);

    //buildHeap，将所有非叶子节点遍历一遍
    for (int i = v.size() / 2; i >= 0; --i)
    {
        down(v, v.size(), i);
    }

    //将最大的取出，塞到数组尾部
    for (int i = 0; i < v.size(); ++i)
    {
        int tmp = v[0];
        v[0] = v[v.size() - i - 1];
        v[v.size() - i - 1] = tmp;
        down(v, v.size() - i - 1, 0);
    }


    cout << "Exercise 7.11:" << endl;
    for (int i = 0;  i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}

void mergeSort(vector<int>& v, int left, int right)
{
    if (right - left == 1)
    {
        if (v[left] > v[right])
        {
            swap(v[left], v[right]);
        }
    }
    else if (right > left)
    {
        int center = (left + right) / 2;
        mergeSort(v, left, center);
        mergeSort(v, center + 1, right);

        int i = left, j = center + 1;
        vector<int> tmp;
        while (i <= center && j <= right)
        {
            if (v[i] < v[j])
            {
                tmp.push_back(v[i]);
                ++i;
            }
            else
            {
                tmp.push_back(v[j]);
                ++j;
            }
        }
        if (i > center)
        {
            while (j <= right)
            {
                tmp.push_back(v[j++]);
            }
        }
        else if (j > right)
        {
            while (i <= center)
            {
                tmp.push_back(v[i++]);
            }
        }

        for (int k = left, m = 0; k <= right && m < tmp.size(); ++k, ++m)
        {
            v[k] = tmp[m];
        }
    }
}

void e7_15()
{
    vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(1);
    v.push_back(5);
    v.push_back(9);
    v.push_back(2);
    v.push_back(6);

    mergeSort(v, 0, v.size() - 1);

    cout << "Exercise 7.15:" << endl;
    for (int i = 0;  i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}

void e7_16()
{
    vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(1);
    v.push_back(5);
    v.push_back(9);
    v.push_back(2);
    v.push_back(6);

    for (int i = 1; i < v.size(); i *= 2)
    {
        for (int j = 0; j < v.size(); j += i * 2)
        {
            int left = j, right = j + i * 2 - 1, center = (left + right) / 2;
            int k = left, m = center + 1;
            vector<int> tmp;
            while (k <= center && m <= right)
            {
                if (v[k] < v[m])
                {
                    tmp.push_back(v[k]);
                    ++k;
                }
                else
                {
                    tmp.push_back(v[m]);
                    ++m;
                }
            }
            if (k > center)
            {
                while (m <= right)
                {
                    tmp.push_back(v[m++]);
                }
            }
            else if (m > right)
            {
                while (k <= center)
                {
                    tmp.push_back(v[k++]);
                }
            }

            for (int n = left, s = 0; n <= right && s < tmp.size(); ++n, ++s)
            {
                v[n] = tmp[s];
            }
        }
    }

    cout << "Exercise 7.16:" << endl;
    for (int i = 0;  i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}

//快速选择第k大的数
int quickSelect(vector<int>& v, int left, int right, int k)
{
    if (right - left + 1 <= 3)
    {
        //如果元素数比较小，则选择插入排序，然后返回第k位
        int j = left;
        for (int i = left + 1; i <= right; ++i)
        {
            int tmp = v[i];
            for (j = i; j - 1>= 0; --j)
            {
                if (tmp < v[j - 1])
                {
                    v[j] = v[j - 1];
                }
                else
                {
                    break;
                }
            }
            v[j] = tmp;
        }
        return v[k];
    }
    else
    {   //快速选择
        
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
        if (v[right] > v[center])
        {
            swap(v[right], v[center]);
        }

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
        swap(v[i], v[right - 2]);

        //s1 + 1 == k
        int s1 = i - left;
        if (s1 + 1 == k)
        {
            return v[i];
        }
        else if (i - left + 1 < k)
        {
            return quickSelect(v, left, i - 1, k);
        }
        else
        {
            return quickSelect(v, i + 1, right, k - (i - s1 - 1));
        }
    }
}

void e7_29()
{
    vector<int> v;
    v.push_back(142);
    v.push_back(543);
    v.push_back(123);
    v.push_back(65);
    v.push_back(453);
    v.push_back(879);
    v.push_back(572);
    v.push_back(434);
    v.push_back(111);
    v.push_back(242);
    v.push_back(811);
    v.push_back(102);

    cout << quickSelect(v, 0, v.size(), 6) << endl;
}

int main()
{
    e7_1();
    cout << endl;

    e7_4();
    cout << endl;

    e7_11();
    cout << endl;

    e7_15();
    cout << endl;

    e7_16();
    cout << endl;

    e7_29();
    cout << endl;

    return 0;
}

