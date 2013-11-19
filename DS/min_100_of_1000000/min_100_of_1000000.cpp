#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
��100���������ѡ����С��100�� 
�����ⲻ�ʺ��ÿ���ѡ����������Ϊ100����������ڴ棬����̫�� 
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
        //ѡ����ŦԪ
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

        //����ŦԪ�ŵ��Ƚ�������
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
        //����ŦԪ�ŻرȽ�����
        swap(v[i], v[right - 1]);
        
        quickSort(v, left, i - 1);
        quickSort(v, i + 1, right);
    }
}



/*
����һ�� 
ѡȡǰ100��������һ�������У�������������� 
����ʣ�µ�Ԫ�أ����Ԫ��С������ĵ�100������ɾ����100�����Ѵ�Ԫ�ز��뵽�������ȷλ���ϡ� 
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

    //��v���п�������
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
�������� 
ѡȡǰ100��������һ��������У�����ڸ��ϣ���
����ʣ�µ�Ԫ�أ����Ԫ��С������ĵ�1������ɾ����1�����Ѵ�Ԫ�ز��뵽�������ȷλ���� 
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

