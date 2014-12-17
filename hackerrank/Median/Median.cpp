/*
https://www.hackerrank.com/challenges/median
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
/* Head ends here */

void print(const vector<int>& v) {
    int size = v.size();
    if (size % 2) {
        // odd
        cout << v[size / 2] << endl;
    } else {
        // even
        long tmp = long(v[size / 2 - 1]) + v[size / 2];
        if (tmp % 2) {
            long v = tmp / 2;
            if (v == 0 && tmp < 0) {
                cout << "-0.5" << endl;
            } else {
                cout << tmp / 2 << ".5" << endl;
            }
        } else {
            cout << tmp / 2 << endl;
        }
    }
}

// 朴素实现
void median2(vector<char> s, vector<int> X) {
    vector<int> v;
    for (int i = 0; i < s.size(); ++i) {
        if ('r' == s[i]) {
            vector<int>::iterator it = v.begin();
            while (it != v.end()) {
                if (*it == X[i]) {
                    break;
                }
                ++it;
            }
            if (it == v.end()) {
                cout << "Wrong!" << endl;
            } else {
                v.erase(it);
                int size = v.size();
                if (v.empty()) {
                    cout << "Wrong!" << endl;
                } else {
                    print(v);
                }
            }
        } else if ('a' == s[i]) {
            bool inserted = false;
            for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
                if (X[i] < *it) {
                    v.insert(it, X[i]);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {
                v.push_back(X[i]);
            }
            print(v);
        }
    }
}

//查找的时候使用折半查找
void median(vector<char> s, vector<int> X) {
    vector<int> v;
    for (int i = 0; i < s.size(); ++i) {
        if ('r' == s[i]) {
            int lo = 0, hi = v.size() - 1;
            bool found = false;
            while (lo <= hi) {
                int mid = (hi + lo) / 2;
                if (v[mid] == X[i]) {
                    lo = mid;
                    found = true;
                    break;
                } else if (v[mid] < X[i]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (!found) {
                cout << "Wrong!" << endl;
            } else {
                v.erase(v.begin() + lo);
                int size = v.size();
                if (v.empty()) {
                    cout << "Wrong!" << endl;
                } else {
                    print(v);
                }
            }
        } else if ('a' == s[i]) {
            int lo = 0, hi = v.size() - 1;
            while (lo <= hi) {
                int mid = (hi + lo) / 2;
                if (v[mid] > X[i]) {
                    hi = mid - 1;
                } else if (v[mid] < X[i]) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                    break;
                }
            }

            if (v.empty()) {
                v.push_back(X[i]);
            } else {
                v.insert(v.begin() + hi + 1, X[i]);
            }
            print(v);
        }
    }
}

int main(void){
    //Helpers for input and output
   int N;
   cin >> N;
   
   vector<char> s;
   vector<int> X;
   char temp;
   int tempint;
   for(int i = 0; i < N; i++){
        cin >> temp >> tempint;
        s.push_back(temp);
        X.push_back(tempint);
   }
   
   median(s,X);
   return 0;
}
