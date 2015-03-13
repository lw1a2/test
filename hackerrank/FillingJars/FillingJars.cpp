#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, M;
    cin >> N >> M;
    long sugar = 0;

    for (int i = 0; i < M; ++i) {
        int a;
        cin >> a;
        int b;
        cin >> b;
        long k;
        cin >> k;
        sugar += (b - a + 1) * k;
    }

    cout << sugar / N << endl;

    return 0;
}
