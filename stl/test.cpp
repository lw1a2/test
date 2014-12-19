#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> 

using namespace std;

int main()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);

    sort(v.begin(), v.end(), greater<int>());

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    return 0;
}