#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, T;
    cin >> N >> T;
    vector<int> v(N);
    for (int i = 0; i < N; ++i) {
        int width;
        cin >> width;
        v[i] = width;
    }

    for (int k = 0; k < T; ++k) {
        int i, j;
        cin >> i >> j;
        int min = 4;
        for (int m = i; m <= j; ++m) {
            if (v[m] < min) {
                min = v[m];
            }
        }
        cout << min << endl;
    }

    return 0;
}
