/*
https://www.hackerrank.com/challenges/stockmax
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//感觉这个问题和动态规划没啥关系，没有重叠子结构
long f(const vector<long>& v, int start, int end) {
    if (end - start < 1) {
        return 0;
    }

    long max = 0;
    int max_i = 0;

    for (int i = start; i <= end; ++i) {
        if (max < v[i]) {
            max = v[i];
            max_i = i;
        }
    }

    if (max == 0) {
        // 此区段单调递减
        return 0;
    }


    // 当前区域会被分为两个区域：
    // 1）最大点左边的：全部买进，然后在最大点卖出
    // 2）最大点右边的：递归
    long r = 0;
    long buy = 0;
    for (int i = start; i < max_i; ++i) {
        buy += v[i];
    }
    r = max * (max_i - start) - buy;

    return r + f(v, max_i + 1, end);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int lines = 0;

    cin >> lines;
    for (int i = 0; i < lines; ++i) {
        int n;
        cin >> n;

        vector<long> v;
        for (int j = 0; j < n; ++j) {
            long tmp;
            cin >> tmp;
            v.push_back(tmp);
        }

        cout << f(v, 0, v.size() - 1) << endl;
    }

    return 0;
}
