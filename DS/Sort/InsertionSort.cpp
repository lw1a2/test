#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& v)
{
    for (int i = 1; i < v.size(); ++i) {
        int j = i - 1;
        int key = v[i];
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = key;
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

    f2(insertionSort);

    return 0;
}

