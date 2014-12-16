#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n = 0;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    vector<int> counts;

    for (int i = 0; i < v.size(); ++i) {
        int j = v[i];
        vector<int> d;
        while (j) {
            int tmp = j % 10;
            if (tmp != 0) {
                d.push_back(tmp);
            }
            j /= 10;
        }

        int count = 0;
        for (int j = 0; j < d.size(); ++j) {
            if (v[i] % d[j] == 0) {
                ++count;
            }
        }
        counts.push_back(count);
    }

    for (int i = 0; i < counts.size(); ++i) {
        cout << counts[i] << endl;
    }

    return 0;
}

