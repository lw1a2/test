#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int N, K, unfairness = INT_MAX;
    cin >> N >> K;
    int list[N];
    for (int i=0; i<N; i++)
        cin >> list[i];
    
    /** Write the solution code here. Compute the result, store in  the variable unfairness --
    and output it**/
    vector<int> sorted_list(list, list + N);
    sort(sorted_list.begin(), sorted_list.end());

    for (int i = 0; i < N && i + K - 1 < N; ++i) {
        int tmp = sorted_list[i + K - 1] - sorted_list[i];
        if (tmp < unfairness) {
            unfairness = tmp;
        }
    }
   
    cout << unfairness << "\n";
    return 0;
}
