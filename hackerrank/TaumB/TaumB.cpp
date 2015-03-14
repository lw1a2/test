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
        long B, W, X, Y, Z;
        cin >> B >> W >> X >> Y >> Z;
        if (X >= Y) {
            if (X - Y <= Z) {
                cout << B * X + W * Y << endl;    
            } else {
                cout << B * (Y + Z) + W * Y << endl;
            }
        } else {
            if (Y - X <= Z) {
                cout << B * X + W * Y << endl;    
            } else {
                cout << B * X + W * (X + Z) << endl;
            }
        }
    }
    return 0;
}
