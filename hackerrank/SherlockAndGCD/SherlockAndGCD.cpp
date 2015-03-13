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
        int N;
        cin >> N;
        int min = 100001;
        vector<int> vec(N);
        for (int j = 0; j < N; ++j) {
            int d;
            cin >> d;
            vec[j] = d;
            if (d < min && d > 1) {
                min = d;
            }
        }
        bool yes = false;
        for (int j = 0; j < N; ++j) {
            if (vec[j] % min) {
                cout << "YES" << endl;
                yes = true;
                break;
            }
        }
        if (!yes) {
            cout << "NO" << endl;
        }
    }
    return 0;
}
