#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    char c;
    bool pangram = false;
    vector<int> v(26, 0);
    int count = 0;
    while (cin >> c) {
        int i = 0;
        if (c >= 'A' && c <= 'Z') {
            i = c - 'A';
        } else if (c >= 'a' && c <= 'z') {
            i = c - 'a';
        } else {
            continue;
        }

        if (v[i] == 0) {
            v[i] = 1;
            if (++count == 26) {
                pangram = true;
                break;
            }
        }
    }

    if (pangram) {
        cout << "pangram" << endl;
    } else {
        cout << "not pangram" << endl;
    }

    return 0;
}
