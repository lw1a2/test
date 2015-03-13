#include <iostream>
using namespace std;

int height(int n) {
    int h = 1;
    for (int i = 1; i <= n; ++i) {
        if (i % 2) {
            h *= 2;
        } else {
            h += 1;
        }
    }
    return h;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << height(n) << endl;
    }
}
