#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        string w;
        cin >> w;
        bool found = false;
        int j;
        for (j = w.size() - 2; j >= 0 && !found; --j) {
            for (int k = j + 1; k < w.size() && !found; ++k) {
                // 从尾部开始，找到第一个升序的字符串，如...a...c...
                if (w[j] < w[k]) {
                    int min = k;
                    for (int m = k + 1; m < w.size(); ++m) {
                        // 找到c之后的最小字符，如...a...c...b
                        if (w[m] < w[min] && w[j] < w[m]) {
                            min = m;
                        }
                    }
                    // 交换a和b
                    swap(w[j], w[min]);
                    found = true;
                }
            }
        }
        if (found) {
            // 把b之后的字符串升序排列
            sort(w.begin() + j + 2, w.end());
            cout << w << endl;
        } else {
            cout << "no answer" << endl;
        }
    }
    return 0;
}
