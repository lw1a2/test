#include <iostream>
#include <vector>

using namespace std;

/* 
���� 
4, 5, 6, 1, 2, 3 
������Ϊ�������飬1Ϊ��ͷ
�ڻ������������Ԫ���Ƿ���� 
*/

bool findInRing(const vector<int>& v, int left, int right, const int key)
{
    if (left == right)
    {
        if (v[left] == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (right > left)
    {
        int center = (left + right) / 2;
        if (v[center] == key)
        {
            return true;
        }
        else if (v[left] <= v[center] && v[center] <= v[right])   //left��center������
        {
            if (v[left] <= key && key <= v[right])
            {
                if (v[center] > key)
                {
                    return findInRing(v, left, center - 1, key);
                }
                else
                {
                    return findInRing(v, center + 1, right, key);
                }
            }
            else
            {
                return false;
            }
        }
        else if (v[left] >= v[center] && v[center] >= v[right])   //left��center������
        {
            if (v[right] <= key && key <= v[left])
            {
                if (v[center] > key)
                {
                    return findInRing(v, center + 1, right, key);
                }
                else
                {
                    return findInRing(v, left, center - 1, key);
                }
            }
            else
            {
                return false;
            }
        }
        else                                                    //left��center����������ȼ�����
        {
            return findInRing(v, center + 1, right, key) || findInRing(v, left, center - 1, key);
        }
    }

    return false;
}

//�������ҵ��ֽ�㣬Ȼ���ٶ����������ֽ����۰����
//��http://www.gocalf.com/blog/circularly-ordinal-array.html
bool findInRing2(const vector<int>& v, int left, int right, const int key)
{
    return false;
}

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    //v.push_back(8);


    for (int i = 0; i < v.size(); ++i)
    {
        cout << "v: ";
        for (int j = 0; j < v.size(); ++j)
        {
            cout <<v[j] << " ";
        }
        cout << endl;
        for (int k = 0; k < v.size(); ++k)
        {
            cout << "find " << v[k] << ": " << findInRing(v, 0, v.size() - 1, v[k]) << endl;
        }
        cout << "find 0: " << findInRing(v, 0, v.size() - 1, 0) << endl;
        cout << "find 2: " << findInRing(v, 0, v.size() - 1, 2) << endl;
        cout << "find 100: " << findInRing(v, 0, v.size() - 1, 100) << endl;
        cout << endl;

        int tmp = v[0];
        for (int j = 0; j < v.size() - 1; ++j)
        {
            v[j] = v[j + 1];
        }
        v[v.size() - 1] = tmp;
    }

    return 0;
}

