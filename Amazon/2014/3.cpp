#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int> > hills;
    for (int i = 0; i < n; i++) {
        vector<int> hill;
        int a, b, c;
        char m;
        cin >> a >> m >> b >> m >> c;
        hill.push_back(a);
        hill.push_back(b);
        hill.push_back(c);
        hills.push_back(hill);
    }

    int total = 0;
    int i = 0;
    for (; i < hills.size() && i + 1 < hills.size(); i += 2) {
        if (hills[i][1] < hills[i + 1][0]) {
            total += (hills[i][2] + hills[i + 1][2]) * 2;
        } else {
            if (hills[i][2] < hills[i + 1][2]) {
                total += hills[i + 1][2] * 2;
            } else {
                total += hills[i][2] * 2;
            }
        }
    }
    if (i < hills.size()) {
        total += hills[i][2] * 2;
    }

    total += hills[n - 1][1];

    cout << total;

    return 0;
}