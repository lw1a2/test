/*
https://www.hackerrank.com/challenges/stockmax
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int f(const vector<int>& prices) {
    return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n = 0;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;

        vector<int> prices;
        while (cin >> tmp) {
            prices.push_back(tmp);
        }

        cout << f(prices) << endl;
    }

    return 0;
}
