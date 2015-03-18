// https://www.hackerrank.com/challenges/insertionsort1
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
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

void insertionSort(vector<int>& ar) {
    for (int i = 1; i < ar.size(); ++i) {
        int j = i - 1;
        int key = ar[i];
        while (j >= 0 && ar[j] > key) {
            ar[j + 1] = ar[j];
            --j;
            copy(ar.begin(), ar.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
        }
        ar[j + 1] = key;
    }
    copy(ar.begin(), ar.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main(void) {
    vector<int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for (int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
        int _ar_tmp;
        cin >> _ar_tmp;
        _ar.push_back(_ar_tmp); 
    }

    insertionSort(_ar);
   
   return 0;
}
