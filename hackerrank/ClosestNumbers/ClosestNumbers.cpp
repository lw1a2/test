// https://www.hackerrank.com/challenges/closest-numbers

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int tmp = 0;
    cin >> tmp;
    vector<int> v;
    while (cin >> tmp) {
        v.push_back(tmp);
    }

    sort(v.begin(), v.end());

    vector<int> smallest_index;
    int smallest = 10000000;
    for (int i = 0; i + 1 < v.size(); ++i) {
        tmp = abs(v[i] - v[i + 1]);
        if (smallest > tmp) {
            smallest = tmp;
            smallest_index.clear();
            smallest_index.push_back(i);
        } else if (smallest == tmp) {
            smallest_index.push_back(i);
        }
    }

    for (int i = 0; i < smallest_index.size(); ++i) {
        cout << v[smallest_index[i]] << " " << v[smallest_index[i] + 1] << " ";
    }

    return 0;
}
