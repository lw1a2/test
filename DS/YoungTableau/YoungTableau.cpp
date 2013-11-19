/*
���Ͼ��� 
�����������ʣ� 
ÿ�д�С�������У�ÿ�д�С��������
*/

#include <iostream>
#include <vector>

using namespace std;

//�ҵ���һ��δʹ�õĽڵ�
bool findFirstUnused(const vector<vector<int> >& a, int& i, int& j)
{
    if (!a.empty())
    {
        for (i = 0; i < a.size(); ++i)
        {
            if (-1 == a[i][0])
            {
                break;
            }
        }
        --i;

        for (j = 0; j < a[i].size(); ++j)
        {
            if (-1 == a[i][j])
            {
                return true;
            }
        }
    }

    return false;
}

void insert(vector<vector<int> >& a, int v)
{
    int i = 0, j = 0;
    //�ҵ���һ��δʹ�ýڵ�
    bool exist = findFirstUnused(a, i, j);
    if (!exist)
    {
        cout << "Insert " << v << " Failed, All Used" << endl;
        return;
    }
    else
    {
        cout << "Insert " << v << ":" << endl;
    }

    //���丳ֵΪ����������
    a[i][j] = v;

    //�ƶ��ڵ㣬ʹ���󱣳����ʲ���
    int k = i, m = j;
    while (k >= 0 && m >= 0)
    {
        //���Ƶ����ϱ�
        if (0 == k && m != 0)
        {
            //�������ߵ�С���򽻻�
            if (a[k][m] > a[k][m - 1])
            {
                swap(a[k][m], a[k][m - 1]);
                m = m - 1;
            }
            //���򲻶�
            else
            {
                return;
            }
        }
        //���Ƶ������
        else if (k != 0 && 0 == m)
        {
            //������ϱߵ�С���򽻻�
            if (a[k - 1][m] > a[k][m])
            {
                swap(a[k][m], a[k - 1][m]);
                k = k - 1;
            }
            //���򲻶�
            else
            {
                return;
            }
        }
        //���Ƶ����Ͻ�
        else if (0 == k && 0 == m)
        {
            return;
        }
        else
        {
            int max_i = 0, max_j = 0, min_i = 0, min_j = 0;
            if (a[k - 1][m] > a[k][m - 1])
            {
                max_i = k - 1;
                max_j = m;
                min_i = k;
                min_j = m - 1;
            }
            else
            {
                min_i = k - 1;
                min_j = m;
                max_i = k;
                max_j = m - 1;
            }
            //����С��С����ʹ�Ľ���
            if (a[k][m] < a[min_i][min_j])
            {

                swap(a[k][m], a[max_i][max_j]);
                k = max_i;
                m = max_j;
            }
            //��������֮�䣬��ʹ�Ľ���
            else if (a[min_i][min_j] < a[k][m] && a[k][m] < a[max_i][max_j])
            {
                swap(a[k][m], a[max_i][max_j]);
                k = max_i;
                m = max_j;
            }
            //���򲻶�
            else
            {
                return;
            }

            //��ʵ������㷨���Լ򻯣����ǲ�����⣩��
            //���������С��������Ľ��������򲻶�
        }
    }
}

//�ҵ����һ���ڵ�
void findLast(const vector<vector<int> >& a, int& last_i, int& last_j)
{
    int i = 0, j = 0;
    bool exist = findFirstUnused(a, i, j);
    if (exist)
    {
        if (0 == j)
        {
            last_i = i - 1;
            last_j = a[0].size() - 1;
        }
        else
        {
            last_i = i;
            last_j = j - 1;
        }
    }
    else
    {
        last_i = a.size() - 1;
        last_j = a[0].size() - 1;
    }
}

void del(vector<vector<int> >& a, int i, int j)
{
    cout << "Delete [" << i << "][" << j << "]" << endl;
    if (a.empty() || i >= a.size() || j >= a[0].size())
    {
        return;
    }
    if (-1 == a[i][j])
    {
        return;
    }

    int last_i = 0, last_j = 0;
    //�ҵ����һ�����ýڵ�
    findLast(a, last_i, last_j);
    //�������ɾ���ڵ㽻��
    swap(a[i][j], a[last_i][last_j]);
    //�����һ�����ýڵ�ɾ��
    a[last_i][last_j] = -1;
    //�ƶ��ڵ㣬ʹ���󱣳����ʲ���
    int k = i, m = j;
    while (k < a.size() && m < a[0].size())
    {
        //���Ƶ����±�
        if (a.size() - 1 == k && m < a[0].size() - 1)
        {
            //������ұߵĴ��򽻻�
            if (a[k][m + 1] != -1 && a[k][m] > a[k][m + 1])
            {
                swap(a[k][m], a[k][m + 1]);
                m = m + 1;
            }
            //���򲻶�
            else
            {
                return;
            }
        }
        //���Ƶ����ұ�
        else if (k < a.size() - 1 && a[0].size() - 1 == m)
        {
            //������±ߵĴ��򽻻�
            if (a[k + 1][m] != -1 && a[k][m] > a[k + 1][m])
            {
                swap(a[k][m], a[k + 1][m]);
                k = k + 1;
            }
            //���򲻶�
            else
            {
                return;
            }
        }
        //���Ƶ����½�
        else if (a.size() - 1 == k && a[0].size() - 1 == m)
        {
            return;
        }
        else
        {
            //�õ��ұߺ��±��У����ߵ�С��
            int min_i = 0, min_j = 0;
            if (a[k + 1][m] > a[k][m + 1])
            {
                min_i = k;
                min_j = m + 1;
            }
            else
            {
                min_i = k + 1;
                min_j = m;
            }
            //��С�Ľ���
            if (a[min_i][min_j] != -1)
            {
                swap(a[k][m], a[min_i][min_j]);
                k = min_i;
                m = min_j;
            }
            else
            {
                return;
            }
        }
    }
}

void find(const vector<vector<int> >& a, const int v, int& i, int& j)
{
    bool exist = false;
    i = a.size() - 1;
    j = 0;
    while (i >= 0 && j < a[0].size())
    {
        if (v > a[i][j])
        {
            ++j;
        }
        else if (v < a[i][j])
        {
            --i;
        }
        else if (v == a[i][j])
        {
            exist = true;
            break;
        }
    }

    if (exist)
    {
        cout << "Found " << v << " at [" << i << "][" << j <<"]" << endl;
    }
    else
    {
        cout << "Not Found " << v << endl;
    }
}

void print(const vector<vector<int> >& a)
{
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a[0].size(); ++j)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

/*
�������ݣ�-1����ڵ�δ��ֵ����
1  3  5  7 
2  4  8  10 
5  7  9  12 
6  8  13 15 
9  20 -1 -1 
*/

int main()
{
    vector<vector<int> > a;
    vector<int> tmp(4);
    tmp[0] = 1;
    tmp[1] = 3;
    tmp[2] = 5;
    tmp[3] = 7;
    a.push_back(tmp);
    tmp[0] = 2;
    tmp[1] = 4;
    tmp[2] = 8;
    tmp[3] = 10;
    a.push_back(tmp);
    tmp[0] = 5;
    tmp[1] = 7;
    tmp[2] = 9;
    tmp[3] = 12;
    a.push_back(tmp);
    tmp[0] = 6;
    tmp[1] = 8;
    tmp[2] = 13;
    tmp[3] = 15;
    a.push_back(tmp);
    tmp[0] = 9;
    tmp[1] = 20;
    tmp[2] = -1;
    tmp[3] = -1;
    a.push_back(tmp);

    print(a);

    int i = -1, j = -1;
    find(a, 7, i, j);
    find(a, 70, i, j);
    find(a, 1, i, j);
    find(a, 3, i, j);
    find(a, 9, i, j);

    insert(a, 0);
    print(a);
    del(a, 0, 0);
    print(a);
    insert(a, 11);
    print(a);
    del(a, 0, 3);
    print(a);
    insert(a, 3);
    print(a);
    del(a, 4, 0);
    print(a);
    del(a, 4, 3);
    print(a);

    return 0;
}

