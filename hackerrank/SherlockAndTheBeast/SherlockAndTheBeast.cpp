#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int N;
        cin >> N;
        bool found = false;
        for (int a = N / 3; a >= 0 && !found; --a) {
            for (int b = N / 5; b >= 0 && !found; --b) {
                if ((3 * a + 5 * b) == N) {
                    for (int j = 0; j < a; ++j) {
                        cout << "555";
                    }
                    for (int j = 0; j < b; ++j) {
                        cout << "33333";
                    }
                    cout << endl;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << -1 << endl;
        }
    }
    return 0;
}
