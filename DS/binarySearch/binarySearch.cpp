#include <iostream>
#include <vector>

using namespace std;

void binarySearch(const vector<int>& a, int left, int right, int value)
{
    if (left == right)
    {
        if (value == a[left])
        {
            cout << "Found" << endl;
        }
        else
        {
            cout << "Not Found" << endl;
        }
        return;
    }

    int mid = (left + right) / 2;
    if (value < a[mid])
    {
        binarySearch(a, left, mid - 1, value);
    }
    else if (value > a[mid])
    {
        binarySearch(a, mid + 1, right, value);
    }
    else
    {
        cout << "Found" << endl;
    }
}

void binarySearch2(const vector<int>& a, int value)
{
    int left = 0;
    int right = a.size() - 1;
    
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (value < a[mid])
        {
            right = mid - 1;
        }
        else if (value > a[mid])
        {
            left = mid + 1;
        }
        else
        {
            cout << "Found" << endl;
            return;
        }
    }

    cout << "Not Found" << endl;
}

//C语言实现
void binarySearch3(int* a, int size, int value)
{
    int* left = a;
    int* right = a + size - 1;
    
    while (left <= right)
    {
        //int* mid = (right + left) / 2; //直接相加编译不过，要用下面的方法
        int* mid = a + (right - a + left - a) / 2;
        if (value < *mid)
        {
            right = mid - 1;
        }
        else if (value > *mid)
        {
            left = mid + 1;
        }
        else
        {
            cout << "Found" << endl;
            return;
        }
    }

    cout << "Not Found" << endl;
}

int main()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    a.push_back(6);
    a.push_back(9);
    a.push_back(10);
    a.push_back(22);
    a.push_back(100);

    binarySearch(a, 0, a.size() - 1, 22);
    binarySearch(a, 0, a.size() - 1, 3);
    binarySearch(a, 0, a.size() - 1, 6);
    binarySearch(a, 0, a.size() - 1, 9);
    binarySearch(a, 0, a.size() - 1, 0);
    binarySearch(a, 0, a.size() - 1, 1000);
    binarySearch(a, 0, a.size() - 1, 7);

    cout << endl;

    binarySearch2(a, 22);
    binarySearch2(a, 3);
    binarySearch2(a, 6);
    binarySearch2(a, 9);
    binarySearch2(a, 0);
    binarySearch2(a, 1000);
    binarySearch2(a, 7);

    cout << endl;

    int a2[] = {1, 3, 5, 6, 9, 10, 22, 100};
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 22);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 3);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 6);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 9);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 0);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 1000);
    binarySearch3(a2, sizeof(a2)/sizeof(a2[0]), 7);

    return 0;
}

