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
        string s, tmp;
        cin >> s;
        tmp = s;
        int k = 0;
        bool deleted = false;
        while (1) {
            bool need_del = false;
            for (int j = 0; j < tmp.size() / 2; ++j) {
                if (tmp[j] != tmp[tmp.size() - j - 1]) {
                    need_del = true;
                    break;
                }
            }
            if (need_del) {
                tmp = s;
                tmp.erase(tmp.begin() + k, tmp.begin() + k + 1);
                deleted = true;
                ++k;
            } else {
                if (deleted) {
                    cout << k - 1 << endl;
                } else {
                    cout << -1 << endl;
                }
                break;
            }
        }
    }
    return 0;
}
