#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> left, right;
    int l, r;
    while (cin >> l >> r) {
        left.push_back(l);
        right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    long long result = 0;
    for (int i = 0; i < left.size(); i++) {
        result += abs(left[i] - right[i]);
    }
    cout << result << endl;
}
