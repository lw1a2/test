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
    vector<vector<char> > vec(N);
    for (int i = 0; i < N; ++i) {
        char c;
        for (int j = 0; j < M; ++j) {
            cin >> c;
            vec[i].push_back(c);
        }
    }

    int max_team = 0;
    int max_topic = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            int topic = 0;
            for (int k = 0; k < M; ++k) {
                if (vec[i][k] == '1' or vec[j][k] == '1') {
                    ++topic;
                }
            }
            if (topic > max_topic) {
                max_topic = topic;
                max_team = 1;
            } else if (topic == max_topic) {
                ++max_team;
            }
        }
    }

    cout << max_topic << endl;
    cout << max_team << endl;

    return 0;
}
