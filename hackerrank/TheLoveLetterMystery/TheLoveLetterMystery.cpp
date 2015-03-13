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
    vector<string> vec(T);
    for (int i = 0; i < T; ++i) {
        string s;
        cin >> s;
        vec[i] = s;
    }

    for (int i = 0; i < T; ++i) {
        int count = 0;
        string s = vec[i];
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (s[left] != s[right]) {
                if (s[left] < s[right]) {
                    --s[right];
                } else {
                    --s[left];
                }
                ++count;
            }
            ++left;
            --right;
        }
        cout << count << endl;
    }
    return 0;
}
