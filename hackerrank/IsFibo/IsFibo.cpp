/*
https://www.hackerrank.com/challenges/find-digits
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    vector<long> v;
    long tmp = 0;
    cin >> tmp;

    while (cin >> tmp) {
        v.push_back(tmp);
    }

    vector<long> fibs;
    fibs.push_back(0);
    fibs.push_back(1);
    for (int i = 0; i < v.size(); ++i) {
        long n = v[i];
        if (n < 2) {
            cout << "IsFibo" << endl;
        } else {
            long j = 0;
            while (1) {
                long fib = fibs[j] + fibs[j + 1];
                if (j + 2 >= fibs.size()) {
                    fibs.push_back(fib);
                }
                if (fib > n) {
                    cout << "IsNotFibo" << endl;
                    break;
                } else if (fib == n){
                    cout << "IsFibo" << endl;
                    break;    
                }
                ++j;
            }
        }
    }

    return 0;
}
