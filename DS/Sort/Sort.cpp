#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& v)
{
    int count = 0;
    for (int i = 1; i < v.size(); ++i)
    {
        int tmp = v[i];
        int p = i;
        for (; v[p - 1] > tmp && p > 0; --p)
        {
            if (v[p - 1] > tmp)
            {
                v[p] = v[p - 1];
            }
            ++count;
        }
        v[p] = tmp;
    }
    //cout << "count: " << count << endl;
}

void percolateDown(vector<int>& v, int size, int i)
{
    int tmp = v[i];
    int child = i;
    while (child * 2 + 1 < size)
    {
        child = child * 2 + 1;
        if (child + 1 < size && v[child] < v[child + 1])
        {
            ++child;
        }
        if (tmp < v[child])
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

void shellSort(vector<int>& v)
{
    for (int gap = v.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < v.size(); ++i)
        {
            int tmp = v[i];
            int j = i;
            for (; j >= gap && v[j - gap] > tmp; j -= gap)
            {
                if (v[j - gap] > tmp)
                {
                    v[j] = v[j - gap];
                }
            }
            v[j] = tmp;
        }
    }
}

void heapSort(vector<int>& v)
{
    for (int i = v.size() / 2; i >= 0; --i)
    {
        percolateDown(v, v.size(), i);
    }

    for (int i = 0; i < v.size(); ++i)
    {
        int tmp = v[v.size() - i - 1];
        v[v.size() - i - 1] = v[0];
        v[0] = tmp;

        percolateDown(v, v.size() - i - 1, 0);
    }
}

void merge(vector<int>& v, int left, int right)
{
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    vector<int> tmp;
    while (i <= mid && j <= right)
    {
        if (v[i] < v[j])
        {
            tmp.push_back(v[i++]);
        }
        else
        {
            tmp.push_back(v[j++]);
        }
    }

    if (i > mid)
    {
        for (int k = j; k <= right; ++k)
        {
            tmp.push_back(v[k]);
        }
    }
    else
    {
        for (int k = i; k <= mid; ++k)
        {
            tmp.push_back(v[k]);
        }
    }

    for (int k = left, m = 0; m < tmp.size(); ++k, ++m)
    {
        v[k] = tmp[m];
    }
}

void mergeSortHelp(vector<int>& v, int left, int right)
{
    if (left == right)
    {
        return;
    }

    if (left == right - 1)
    {
        if (v[left] > v[right])
        {
            swap(v[left], v[right]);
        }
        return;
    }

    int mid = (left + right) / 2;
    mergeSortHelp(v, left, mid);
    mergeSortHelp(v, mid + 1, right);

    merge(v, left, right);
}

void mergeSort(vector<int>& v)
{
    mergeSortHelp(v, 0, v.size() - 1);
}

void median3(vector<int>& v, int left, int right)
{
    int center = (left + right) / 2;
    if (v[center] < v[left])
    {
        swap(v[center], v[left]);
    }
    if (v[right] < v[left])
    {
        swap(v[right], v[left]);
    }
    if (v[right] < v[center])
    {
        swap(v[right], v[center]);
    }
}

void quickSortHelp(vector<int>& v, int left, int right)
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
        median3(v, left, right);

        swap(v[(left + right) / 2], v[right - 1]);

        int i = left + 1;
        int j = right - 2;

        while (1)
        {
            while (v[i] < v[right - 1])
            {
                ++i;
            }
            while (v[right - 1] < v[j])
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

        swap(v[i], v[right - 1]);

        quickSortHelp(v, left, i - 1);
        quickSortHelp(v, i + 1, right);
    }
}

void quickSort(vector<int>& v)
{
    quickSortHelp(v, 0, v.size() - 1);
}

void bucketSort(vector<int>& v)
{
    int maxBucket = 70;
    vector<int> buckets(70);

    for (int i = 0; i < v.size(); ++i)
    {
        buckets[v[i]] = 1;
    }

    v.clear();

    for (int i = 0; i < buckets.size(); ++i)
    {
        if (buckets[i] == 1)
        {
            v.push_back(i);
        }
    }
}

typedef void SORT(vector<int>& v);
void f(SORT Sort)
{
    vector<int> v;
    v.push_back(32);
    v.push_back(26);
    v.push_back(16);
    v.push_back(67);
    v.push_back(19);
    v.push_back(65);
    v.push_back(24);
    v.push_back(31);
    v.push_back(21);
    v.push_back(13);

    Sort(v);

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
    cout << endl;
}

void countingSort(vector<int>& v)
{
    int MAX = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (MAX < v[i])
        {
            MAX = v[i];
        }
    }
    vector<int> count(MAX + 1);

    for (int i = 0; i < v.size(); ++i)
    {
        ++count[v[i]];
    }

    vector<int> b;
    for (int i = 0; i < count.size();)
    {
        if (count[i]-- > 0)
        {
            b.push_back(i);
        }
        else
        {
            ++i;
        }
    }

    v = b;
}

void radixSort(vector<int>& v)
{
    //确定最大位数
    int MAX = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (MAX < v[i])
        {
            MAX = v[i];
        }
    }
    int count = 0;
    while (MAX)
    {
        ++count;
        MAX /= 10;
    }

    vector<vector<int> > b(10);

    int radix = 1;
    while (count--)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            b[v[i] / radix % 10].push_back(v[i]);
        }
        v.clear();
        for (int m = 0; m < b.size(); ++m)
        {
            for (int n = 0; n < b[m].size(); ++n)
            {
                v.push_back(b[m][n]);
            }
        }
        for (int m = 0; m < b.size(); ++m)
        {
            b[m].clear();
        }

        radix *= 10;
    }
}

typedef void SORT(vector<int>& v);
void f2(SORT Sort)
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

    Sort(v);

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
    cout << endl;
}

int main()
{
    cout << "insertionSort: " << endl;
    f(insertionSort);

    cout << "shellSort: " << endl;
    f(shellSort);

    cout << "heapSort: " << endl;
    f(heapSort);

    cout << "mergeSort: " << endl;
    f(mergeSort);

    cout << "quickSort: " << endl;
    f(quickSort);

    cout << "bucketSort: " << endl;
    f(bucketSort);

    cout << "countingSort: " << endl;
    f2(countingSort);

    cout << "radixSort: " << endl;
    f2(radixSort);

    return 0;
}

