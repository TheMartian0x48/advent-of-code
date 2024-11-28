#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int nextValue(vector<int> &input) {
    int result = 0;
    bool all_zero = false;
    for (int iter = 0; !all_zero && iter < input.size() - 1; iter++) {
        result += input[input.size() - 1 - iter];
        all_zero = true;
        for (int i = 0; i < input.size() - iter - 1; i++) {
            input[i] = input[i + 1] - input[i];
            all_zero = all_zero && input[i] == 0;
        }
    }
    return result;
}

int main() {
    string line;
    int result = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<int> v;
        int t;
        while (ss >> t) v.push_back(t);
        result += nextValue(v);
    }
    cout << result << "\n";
}
