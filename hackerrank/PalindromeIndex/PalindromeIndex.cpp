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
        string s;
        cin >> s;
        bool found = false;
        int left = 0;
        int right = s.size() - 1;
        while (left <= right && !found) {
            if (s[left] != s[right]) {
                int new_left = left + 1;
                int new_right = right;
                found = true;
                while (new_left <= new_right) {
                    if (s[new_left] != s[new_right]) {
                        found = false;
                        break;
                    }
                    ++new_left;
                    --new_right;
                }
                if (found) {
                    cout << left << endl;
                } else {
                    new_left = left;
                    new_right = right - 1;
                    found = true;
                    while (new_left <= new_right) {
                        if (s[new_left] != s[new_right]) {
                            found = false;
                            break;
                        }
                        ++new_left;
                        --new_right;
                    }
                    if (found) {
                        cout << right << endl;
                    } else {
                        cout << -1 << endl;
                        found = true;
                    }
                }
            }
            ++left;
            --right;
        }
        if (!found) {
            cout << -1 << endl;
        }
    }
    return 0;
}
