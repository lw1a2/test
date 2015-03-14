#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin >> n;
    vector<vector<char> > vec(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char d;
            cin >> d;
            vec[i].push_back(d);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                cout << vec[i][j];
            } else if (vec[i][j] > vec[i - 1][j]
                && vec[i][j] > vec[i + 1][j]
                && vec[i][j] > vec[i][j - 1]
                && vec[i][j] > vec[i][j + 1]) {
                    cout << "X";
            } else {
                cout << vec[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}
