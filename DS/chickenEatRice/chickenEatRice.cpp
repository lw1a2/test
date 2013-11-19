#include <vector>
#include <iostream>

using namespace std;

/*
给一个n行m列的矩形框，每个格点都放着若干大米。 
小鸡从左下角点出发，只能往右或者往上走，问小鸡最多能吃掉多少大米。
*/

//递归实现
int chickenEatRice(const vector<vector<int> >& rice, int i, int j)
{
    if (i == 0 && j == 0)
    {
        return rice[0][0];
    }
    else if (i == 0 && j != 0)
    {
        return chickenEatRice(rice, i, j - 1) + rice[i][j];
    }
    else if (i != 0 && j == 0)
    {
        return chickenEatRice(rice, i - 1, j) + rice[i][j];
    }
    else 
    {
        return max(chickenEatRice(rice, i - 1, j), chickenEatRice(rice, i, j - 1)) + rice[i][j];
    }
}

//动态规划
int chickenEatRice2(const vector<vector<int> >& rice, int i, int j)
{
    vector<int> tmp(j + 1, -1);
    vector<vector<int> > c(i + 1, tmp);
    c[0][0] = rice[0][0];

    for (int k = 0; k <= i; ++k)
    {
        for (int r = 0; r <= j; ++r)
        {
            if (c[k][r] == -1)
            {
                if (k == 0 && r != 0)
                {
                    c[k][r] = c[k][r - 1] + rice[k][r];
                }
                else if (k != 0 && r == 0)
                {
                    c[k][r] = c[k - 1][r] + rice[k][r];
                }
                else
                {
                    c[k][r] = max(c[k][r - 1], c[k - 1][r]) + rice[k][r];
                }
            }
        }
    }

    return c[i][j];
}

//动态规划，减少空间复杂度
int chickenEatRice3(const vector<vector<int> >& rice, int i, int j)
{
    vector<int> c(j + 1);

    for (int k = 0; k <= i; ++k)
    {
        for (int r = 0; r <= j; ++r)
        {
            if (k == 0 && r != 0)
            {
                c[r] = c[r - 1] + rice[k][r];
            }
            else if (k != 0 && r == 0)
            {
                c[r] += rice[k][r];
            }
            else
            {
                c[r] = max(c[r], c[r - 1]) + rice[k][r];
            }
        }
    }

    return c[j];
}

int main()
{
    const int n = 10;
    const int m = 10;

    vector<int> tmp(m);
    vector<vector<int> > rice(n, tmp);
    int a[n][m] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            rice[i][j] = a[n - i - 1][j]; //rice的左下角是[0][0]，所以两个数组要翻转一下
        }
    }

    cout << chickenEatRice(rice, n - 1, m - 1) << endl;

    cout << chickenEatRice2(rice, n - 1, m - 1) << endl;

    cout << chickenEatRice3(rice, n - 1, m - 1) << endl;

    return 0;
}

