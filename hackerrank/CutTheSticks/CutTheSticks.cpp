#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin >> N;
    vector<int> vec(N);
    int min = 1001;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        vec[i] = a;
        if (a < min) {
            min = a;
        }
    }

    int next_min = 1001;
    while (1) {
        int cut = 0;
        for (int i = 0; i < N; ++i) {
            if (vec[i] > 0) {
                vec[i] -= min;
                if (vec[i] > 0 && vec[i] < next_min) {
                    next_min = vec[i];
                }
                ++cut;
            }
        }
        if (cut > 0) {
            cout << cut << endl;
        } else {
            break;
        }
        min = next_min;
        next_min = 1001;
    }

    return 0;
}
