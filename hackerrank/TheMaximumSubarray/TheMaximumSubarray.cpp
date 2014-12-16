/*
https://www.hackerrank.com/challenges/maxsubarray
*/

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

    vector<vector<int> > lines;

    for (int i = 0; i < T; ++i) {
        vector<int> line;

        int N = 0;
        cin >> N;

        int tmp = 0;
        for (int j = 0; j < N; ++j) {
            cin >> tmp;
            line.push_back(tmp);
        }
        lines.push_back(line);
    }

    for (int i = 0; i < T; ++i) {
        int maxContSub = 0;
        int maxNonContSub = 0;
        int maxValue = -10000;
        vector<int> line = lines[i];
        int tmp = 0;
        for (int j = 0; j < line.size(); ++j) {
            if (maxValue < line[j]) {
                maxValue = line[j];
            }
            tmp += line[j];
            if (tmp > maxContSub) {
                maxContSub = tmp;
            }
            if (tmp < 0) {
                tmp = 0;
            }

            if (line[j] > 0) {
                maxNonContSub += line[j];
            }
        }

        if (0 == maxNonContSub) {
            maxContSub = maxValue;
            maxNonContSub = maxValue;
        }

        cout << maxContSub << " " << maxNonContSub << endl;
    }

    return 0;
}
