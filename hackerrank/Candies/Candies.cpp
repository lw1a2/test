// https://www.hackerrank.com/challenges/candies

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int f(const vector<int>& v) {
    // C[val]表示值为val的人所组成的数组。
    // C[val][i]表示此数组中第i个人在v里的下标
    vector<vector<int> > C(100001);
    for (int i = 0; i < v.size(); ++i) {
        C[v[i]].push_back(i);
    }

    // 糖果数组
    vector<long> S(v.size(), 1);
    for (int val = 0; val < C.size(); ++val) {
        for (int i = 0; i < C[val].size(); ++i) {
            int index = C[val][i];
            // cout << v[index] << endl;
            if (index > 0) {
                // 左侧有人
                if (v[index - 1] > v[index]) {
                    // 左侧比当前表现好
                    if (S[index - 1] <= S[index]) {
                        S[index - 1] = S[index] + 1;
                    }
                }
            }

            if (index < v.size() - 1) {
                // 右侧有人
                if (v[index + 1] > v[index]) {
                    // 右侧比当前表现好
                    if (S[index + 1] <= S[index]) {
                        S[index + 1] = S[index] + 1;
                    }
                }
            }
        }
    }

    long r = 0;
    for (int i = 0; i < S.size(); ++i) {
        r += S[i];
    }

    for (int i = 0; i + 1 < S.size(); ++i) {
        if (v[i] > v[i + 1]) {
            if (S[i] <= S[i + 1]) {
                int kkk = 0;
            }
        }
    }

    return r;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n;
    cin >> n;

    vector<int> v;
    for (int j = 0; j < n; ++j) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    cout << f(v) << endl;

    return 0;
}
