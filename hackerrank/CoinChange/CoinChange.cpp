/*
https://www.hackerrank.com/challenges/coin-change
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int f(const vector<int>& S, int n, int m, vector<vector<int> >& B) {
    if (n == 0)
        return 1;
    if (n < 0)
        return 0;
    if (m < 0 && n >= 1)
        return 0;

    if (B[n][m] != 0) {
        return B[n][m];
    }
 
    int t = 0;
    if (m - 1 >= 0) {
        B[n][m - 1] = f(S, n, m - 1, B);
        t = B[n][m - 1];
    }
    if (n - S[m] >= 0) {
        B[n - S[m]][m] = f(S, n - S[m], m, B);
        t += B[n - S[m]][m];
    }
    return t;
}

// 没做出来
// 答案：http://www.algorithmist.com/index.php/Coin_Change
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    vector<int> S;
    int n = 0;
    int tmp = 0;
    char c;
    while (cin >> tmp) {
        S.push_back(tmp);
        c = cin.peek();
        if (c != ',') {
            break;
        } else {
            cin >> c;
        }
    }
    cin >> n;

    vector<int> A(S.size(), 0);
    vector<vector<int> > B(n + 1, A);
    cout << f(S, n, S.size() - 1, B) << endl;

    return 0;
}
