#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, M;
    cin >> N >> M;
    vector<vector<int> > v(N + 1);
    for (int i = 1; i <= M; ++i) {
        int ui, vi;
        cin >> ui >> vi;
        v[ui].push_back(vi);
    }

    // for (int i = 1; i <= N; ++i) {
    //     if (!v[i].empty()) {
    //         cout << i << ": ";
    //         for (int j = 0; j < v[i].size(); ++j) {
    //             cout << v[i][j] << ' ';
    //         }
    //         cout << endl;
    //     }
    // }

    vector<bool> done(N + 1);
    int count = 0;
    while (count != N) {
        for (int i = 1; i <= N; ++i) {
            if (done[i]) {
                continue;
            }
            if (v[i].size() == 1) {
                done[i] = true;
            } else {
                bool all_adj_done = true;
                for (int j = 0; j < v[i].size(); ++j) {
                    if (!done[v[i]]) {
                        all_adj_done = false;
                    }
                }
                if (all_adj_done) {
                    done[i] = true;
                }
            }
        }
    }

    return 0;
}
