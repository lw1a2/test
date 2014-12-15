#include <vector>
#include <iostream>

using namespace std;
/*
爬山问题：
从文件中读取山的信息：
第一行代表山的个数；之后的每行，第1列代表上坡的坐标、第2列代表下坡的坐标、第3列代表山的高度
山的形状是垂直的条形。
人从坐标（0, 0）出发，碰到上坡，就爬山，直到到底最顶峰的时候，才下坡（山可能会重叠）。
问人一共走的路程是多少？

如：
输入3_1.txt：
3
1,3,2
2,4,4
6,7,5
输出：
25

三座山都重叠：
输入3_2.txt：
3
1,3,2
2,4,4
3,7,5
输出：
25

解答：
假设文件里的山，已经按照上坡的坐标由小到大进行了排序。
人要走的横轴距离：从0到最后一座山的下坡点的距离。
人要走的纵轴距离：比较相邻的两座山是否重叠，如果重叠则上坡路为高的那座山的高度；不重叠则为两座山的高度和
*/


// 当时答的时候的实现，未处理三座山重叠在一起的情况
int f(const vector<vector<int> >& hills, const int n) {
    int total = 0;
    int i = 0;
    for (; i < hills.size() && i + 1 < hills.size(); i += 2) {
        if (hills[i][1] < hills[i + 1][0]) {
            total += (hills[i][2] + hills[i + 1][2]) * 2;
        } else {
            if (hills[i][2] < hills[i + 1][2]) {
                total += hills[i + 1][2] * 2;
            } else {
                total += hills[i][2] * 2;
            }
        }
    }
    if (i < hills.size()) {
        total += hills[i][2] * 2;
    }

    total += hills[n - 1][1];

    return total;
}

// 正确的实现，考虑每条边
int f2(const vector<vector<int> >& hills, const int n) {
    int total = 0;

    // 纵坐标
    int i = 0;
    for (; i < hills.size() && i + 1 < hills.size(); ++i) {
        if (hills[i][1] < hills[i + 1][0]) {
            // 不重叠
            total += hills[i][2] + hills[i + 1][2];
        } else {
            // 重叠，取高的
            if (hills[i][2] < hills[i + 1][2]) {
                total += hills[i + 1][2];
            } else {
                total += hills[i][2];
            }
        }
    }
    if (i < hills.size()) {
        total += hills[i][2];
    }

    // 横坐标
    total += hills[n - 1][1];

    return total;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int> > hills;
    for (int i = 0; i < n; i++) {
        vector<int> hill;
        int a, b, c;
        char m;
        cin >> a >> m >> b >> m >> c;
        hill.push_back(a);
        hill.push_back(b);
        hill.push_back(c);
        hills.push_back(hill);
    }

    cout << f(hills, n) << endl;

    cout << f2(hills, n) << endl;

    return 0;
}