#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int prevValue(vector<int> &input) {
    int result = 0;
    vector<int> values;
    bool all_zero = false;
    for (int iter = 0; !all_zero && iter < input.size() - 1; iter++) {
        values.push_back(input[0]);
        all_zero = true;
        for (int i = 0; i < input.size() - iter - 1; i++) {
            input[i] = input[i + 1] - input[i];
            all_zero = all_zero && input[i] == 0;
        }
    }
    for (int i = 0; i < values.size(); i++) {
        if (i & 1)
            result -= values[i];
        else
            result += values[i];
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
        result += prevValue(v);
    }
    cout << result << "\n";
}
