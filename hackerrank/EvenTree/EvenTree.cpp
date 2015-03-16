#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int cut_count = 0;
set<int> s;

void f(vector<vector<int> >& v, int i) {
    s.insert(i);
    // all adjacencies
    for (int j = 0; j < v[i].size();) {
        bool is_cut = false;
        if (s.count(v[i][j]) == 0) {
            f(v, v[i][j]);
            if (!(v[v[i][j]].size() % 2)) {
                vector<int>::iterator pos = find(v[i].begin(), v[i].end(), v[i][j]);
                if (pos != v[i].end()) {
                    v[i].erase(pos);
                    is_cut = true;
                }
                ++cut_count;
            }
        }
        if (!is_cut) {
            ++j;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, M;
    cin >> N >> M;
    vector<vector<int> > v(N + 1);
    for (int i = 1; i <= M; ++i) {
        int ui, vi;
        cin >> ui >> vi;
        v[ui].push_back(vi);
        v[vi].push_back(ui);
    }

    f(v, 1);

    cout << cut_count << endl;

    return 0;
}
