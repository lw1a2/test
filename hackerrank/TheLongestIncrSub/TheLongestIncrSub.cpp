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

    return r[i];
}

// 非递归实现，性能略好
int LIS3(const vector<int>& v) {
    if (v.empty()) {
        return 0;
    }

    // M[len] = i：表示为了得到len长度的序列，所需要的最小索引为i。
    // 我们总是在M[len]里保存较小的索引，这样可以得到更长的序列。
    // v[M[len]]：长度为len的序列的最后一个元素。可知v[M[len]]是递增的。
    vector<int> M(v.size() + 1, 0);
    // 当前的最大长度
    int len = 1;

    for (int i = 1; i < v.size(); ++i) {
        if (v[M[len]] < v[i]) {
            // 如果v[M[len]] < v[i]，则把v[i]加入到最长序列里，可以得到新的最长序列
            M[++len] = i;
        } else {
            // 否则，查找M中v[i] < v[M[j]]的元素，更新它的最小索引为i
            // 因为v[M[len]]是递增的，这里可以使用折半查找来确定j的位置，进一步加快速度（未实现）
            for (int j = 1; j <= len; ++j) {
                if (v[i] <= v[M[j]]) {
                    M[j] = i;
                    break;
                }
            }
        }
    }

    return len;
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

    vector<int> r;
    int longest = 0;

    // 实现1
    // r[i]表示包含节点v[i]的最长升序序列长度
    // r.assign(N, 0);
    // for (int i = 0; i < v.size(); ++i) {
    //     int tmp = LIS(v, r, i);
    //     if (longest < tmp) {
    //         longest = tmp;
    //     }
    // }
    // cout << longest << endl;

    // 实现2
    // r[i]表示包含节点v[i]的最长升序序列长度
    // r.assign(N, 1);
    // for (int i = v.size() - 1; i >= 0; --i) {
    //     int tmp = LIS2(v, r, i);
    //     if (longest < tmp) {
    //         longest = tmp;
    //     }
    // }
    // cout << longest << endl;

    // 实现3
    cout << LIS3(v) << endl;
    
    return 0;
}
