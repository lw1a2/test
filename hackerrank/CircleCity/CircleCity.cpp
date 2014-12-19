// https://www.hackerrank.com/challenges/circle-city

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N = 0;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int r_sqr = 0;
        cin >> r_sqr;
        int k = 0;
        cin >> k;
        int min = (int)sqrt(r_sqr / 2);
        if (min == 0) {
            min = 1;
        }
        int r = (int)sqrt(r_sqr);

        int need = 0;

        for (int x = min; x <= r; ++x) {
            for (int y = x + 1; y <= r; ++y) {
                if (x * x + y * y == r_sqr) {
                    // cout << "x: " << x << ", y: " << y << endl;
                    ++need;
                }
            }
        }
        need = need * 4 * 2 + 4;
        // cout << need << endl;
        if (need > k) {
            cout << "impossible" << endl;
        } else {
            cout << "possible" << endl;
        }
    }

    return 0;
}
