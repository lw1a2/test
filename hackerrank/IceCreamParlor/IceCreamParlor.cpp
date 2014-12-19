// https://www.hackerrank.com/challenges/icecream-parlor

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int T = 0;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int M = 0;
        cin >> M;

        int N = 0;
        cin >> N;
        vector<int> v(N + 1);
        vector<vector<int> > A(10001);
        for (int j = 1; j <= N; ++j) {
            int tmp;
            cin >> tmp;
            v[j] = tmp;
            A[tmp].push_back(j);
        }

        for (int j = 1; j <= N; ++j) {
            int peer = M - v[j];
            if (peer >= 0 && !A[peer].empty()) {
                if (A[peer][0] != j) {
                    cout << j << " " << A[peer][0] << endl;
                    break;
                } else {
                    if (A[peer].size() == 2) {
                        cout << j << " " << A[peer][1] << endl;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
