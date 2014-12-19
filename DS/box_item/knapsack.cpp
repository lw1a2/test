// 0-1背包问题

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int f(const vector<int>& v, const vector<int>& w, int T, vector<vector<int> >& m)
{
    for (int i = 1; i <= v.size(); ++i) {
        for (int j = 0; j <= T; ++j) {
            if (w[i - 1] > j) {
                //当前包裹已经超过了重量上限
                m[i][j] = m[i - 1][j];
            } else {
                //这边没怎么理解
                m[i][j] = max(m[i - 1][j], m[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    return m[v.size()][T];
}

int main()
{
    //每个包裹的价值
    vector<int> v;
    v.push_back(60);
    v.push_back(100);
    v.push_back(120);

    //每个包裹的重量
    vector<int> w;
    w.push_back(10);
    w.push_back(20);
    w.push_back(30);

    //能背的总重量
    int T = 50;

    //m[i][j]表示最多背到第i个包裹，重量上限是j时的价值
    vector<int> tmp(T + 1, 0);
    vector<vector<int> > m(v.size() + 1, tmp);

    cout << f(v, w, T, m) << endl;

    return 0;
}

