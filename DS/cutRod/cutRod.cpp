#include <vector>
#include <iostream>

using namespace std;

/*
出售一段长度为i英寸的钢条。不同长度的钢条，售价不同，如：
长度：1 2 3 4 5  6  7  8  9  10
售价：1 5 8 9 10 17 17 20 24 30
如何切割，能使总售价最大。

对钢条做一次切割，原问题变成了更小的子问题：左边的不需要再切割（最优），右边的需要继续切割。
*/

vector<int> prices;

// 保存长度为1..n的所有钢条的最大售价
vector<int> r;

// 递归实现
int cutRodHelp(int i)
{
    if (i == 0) {
        return 0;
    }
 
    if (r[i] != 0) {
        return r[i];
    }

    int q = 0;
    for (int j = 1; j <= i; ++j) {
        q = max(q, prices[j] + cutRodHelp(i - j));
    }

    r[i] = q;
    return r[i];
}

void cutRod(int i) 
{
    cout << cutRodHelp(7) << endl;
}

// 非递归实现
void cutRod2(int i)
{
    for (int j = 1; j <= i; ++j) {
        int q = 0;
        for (int n = 1; n <= j; ++n) {
            q = max(q, prices[n] + r[j - n]);
        }
        r[j] = q;
    }

    cout << r[i] << endl;
}

// 非递归实现，打印切割方法
void cutRod3(int i)
{
    // s[n]表示规模为n时，左边钢条的切割长度
    vector<int> s(i + 1, 0);

    for (int j = 1; j <= i; ++j) {
        int q = 0;
        for (int n = 1; n <= j; ++n) {
            if (q < prices[n] + r[j - n]) {
                q = prices[n] + r[j - n];
                s[j] = n;
            }
        }
        r[j] = q;
    }

    cout << r[i] << ": ";

    int n = i;
    while (n > 0) {
        cout << s[n] << " ";  // 输出规模为n时，左边钢条的切割长度
        n = n - s[n]; // 减去左边钢条的切割长度，为剩下的规模
    }

    cout << endl;
}

int main()
{
    prices.push_back(0);
    prices.push_back(1);
    prices.push_back(5);
    prices.push_back(8);
    prices.push_back(9);
    prices.push_back(10);
    prices.push_back(17);
    prices.push_back(17);
    prices.push_back(20);
    prices.push_back(24);
    prices.push_back(30);

    r.assign(7 + 1, 0);
    cutRod(7);

    r.assign(7 + 1, 0);
    cutRod2(7);

    r.assign(7 + 1, 0);
    cutRod3(7);

    return 0;
}
