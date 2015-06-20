#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void f1() {
    int T;
    cin >> T;
    vector<vector<long> > vec(T);
    long max = 0;
    for (int i = 0; i < T; ++i) {
        long a, b;
        cin >> a;
        cin >> b;
        vec[i].push_back(a);
        vec[i].push_back(b);
        if (b > max) {
            max = b;
        }
    }

    long max_sqrt = (long) sqrt(max);
    vector<long> sqr;
    for (long i = 1; i <= max_sqrt; ++i) {
        sqr.push_back(i * i);
    }

    for (int i = 0; i < T; ++i) {
        int count = 0;
        for (int j = 0; j < sqr.size(); ++j) {
            if (vec[i][0] <= sqr[j] && sqr[j] <= vec[i][1]) {
                ++count;
            } else if (sqr[j] > vec[i][1]) {
                break;
            }
        }
        cout << count << endl;
    }
}

void f2() {
    int T;
    cin >> T;
    long max = 0;
    for (int i = 0; i < T; ++i) {
        long begin, end;
        cin >> begin;
        cin >> end;
        
        long begin_sqrt = (long) sqrt(begin);
        long begin_end = (long) sqrt(end);
        int count = 0;
        for (int j = begin_sqrt; j <= begin_end; ++j) {
            if (begin <= j *j && j * j <= end) {
                ++count;
            }
        }
        cout << count << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    // f1();

    f2();

    return 0;
}
