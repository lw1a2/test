#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int N, K;
        int on_time = 0;
        cin >> N >> K;
        for (int j = 0; j < N; ++j) {
            int a;
            cin >> a;
            if (a <= 0) {
                ++on_time;
            }
        }
        if (on_time < K) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
