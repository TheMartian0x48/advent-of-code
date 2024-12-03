#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> left, right;
    int l, r;
    while (cin >> l >> r) {
        left[l]++;
        right[r]++;
    }

    long long result = 0;
    for (auto iter = left.begin(); iter != left.end(); iter++) {
        result += (1LL * iter->first * iter->second) * right[iter->first];
    }
    cout << result << endl;
}
