/*
https://www.hackerrank.com/challenges/longest-increasing-subsequent
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 带备忘的递归实现，性能不佳，有些用例过不了
int LIS(const vector<int>& v, vector<int>& r, int i) {
    if (r[i] != 0) {
        return r[i];
    }

    for (int j = i + 1; j < v.size(); ++j) {
        if (v[i] < v[j]) {
            // v[i] < v[j]，说明r[i] = 1 + r[j]
            int q = 0;
            if (r[j] != 0) {
                // 有备忘
                q = 1 + r[j];
            } else {
                // 无备忘
                q = 1 + LIS(v, r, j);
            }
            if (r[i] < q) {
                r[i] = q;
            }
        }
    }

    if (0 == r[i]) {
        r[i] = 1;
    }
    return r[i];
}

// 非递归实现，性能不佳，有些用例过不了
int LIS2(const vector<int>& v, vector<int>& r, int i) {
    for (int j = i + 1; j < v.size(); ++j) {
        if (v[i] < v[j]) {
            // v[i] < v[j]，说明r[i] = 1 + r[j]
            if (r[i] < 1 + r[j]) {
                r[i] = 1 + r[j];
            }
        }
    }

    if (0 == r[i]) {
        r[i] = 1;
    }
    return r[i];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int N = 0;
    cin >> N;

    int tmp = 0;
    vector<int> v(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        v[i] = tmp;
    }

    // r[i]表示包含节点v[i]的最长升序序列长度
    vector<int> r(N, 0);
    int longest = 0;

    // 实现1
    // for (int i = 0; i < v.size(); ++i) {
    //     int tmp = LIS(v, r, i);
    //     if (longest < tmp) {
    //         longest = tmp;
    //     }
    // }
    // cout << longest << endl;

    // 实现2
    r[r.size() - 1] = 1;
    for (int i = v.size() - 1; i >= 0; --i) {
        int tmp = LIS2(v, r, i);
        if (longest < tmp) {
            longest = tmp;
        }
    }
    cout << longest << endl;
    
    return 0;
}
