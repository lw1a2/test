/*
杨氏矩阵 
具有如下性质： 
每行从小到大排列，每列从小到大排列
*/

#include <iostream>
#include <vector>

using namespace std;

//找到第一个未使用的节点
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
    //找到第一个未使用节点
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

    //将其赋值为待插入数据
    a[i][j] = v;

    //移动节点，使矩阵保持性质不变
    int k = i, m = j;
    while (k >= 0 && m >= 0)
    {
        //已移到最上边
        if (0 == k && m != 0)
        {
            //如果比左边的小，则交换
            if (a[k][m] > a[k][m - 1])
            {
                swap(a[k][m], a[k][m - 1]);
                m = m - 1;
            }
            //否则不动
            else
            {
                return;
            }
        }
        //已移到最左边
        else if (k != 0 && 0 == m)
        {
            //如果比上边的小，则交换
            if (a[k - 1][m] > a[k][m])
            {
                swap(a[k][m], a[k - 1][m]);
                k = k - 1;
            }
            //否则不动
            else
            {
                return;
            }
        }
        //已移到左上角
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
            //比最小的小，则和大的交换
            if (a[k][m] < a[min_i][min_j])
            {

                swap(a[k][m], a[max_i][max_j]);
                k = max_i;
                m = max_j;
            }
            //处在两者之间，则和大的交换
            else if (a[min_i][min_j] < a[k][m] && a[k][m] < a[max_i][max_j])
            {
                swap(a[k][m], a[max_i][max_j]);
                k = max_i;
                m = max_j;
            }
            //否则不动
            else
            {
                return;
            }

            //其实上面的算法可以简化（但是不好理解）：
            //如果比最大的小，则和最大的交换，否则不动
        }
    }
}

//找到最后一个节点
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
    //找到最后一个已用节点
    findLast(a, last_i, last_j);
    //将其与待删除节点交换
    swap(a[i][j], a[last_i][last_j]);
    //把最后一个已用节点删除
    a[last_i][last_j] = -1;
    //移动节点，使矩阵保持性质不变
    int k = i, m = j;
    while (k < a.size() && m < a[0].size())
    {
        //已移到最下边
        if (a.size() - 1 == k && m < a[0].size() - 1)
        {
            //如果比右边的大，则交换
            if (a[k][m + 1] != -1 && a[k][m] > a[k][m + 1])
            {
                swap(a[k][m], a[k][m + 1]);
                m = m + 1;
            }
            //否则不动
            else
            {
                return;
            }
        }
        //已移到最右边
        else if (k < a.size() - 1 && a[0].size() - 1 == m)
        {
            //如果比下边的大，则交换
            if (a[k + 1][m] != -1 && a[k][m] > a[k + 1][m])
            {
                swap(a[k][m], a[k + 1][m]);
                k = k + 1;
            }
            //否则不动
            else
            {
                return;
            }
        }
        //已移到右下角
        else if (a.size() - 1 == k && a[0].size() - 1 == m)
        {
            return;
        }
        else
        {
            //得到右边和下边中，两者的小者
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
            //和小的交换
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
测试数据（-1代表节点未赋值）：
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

