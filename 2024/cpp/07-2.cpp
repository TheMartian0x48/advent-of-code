#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isPossible(const vector<long long> &operands, long long target, int idx, long long cur_target) {
    if (cur_target > target)
        return false;
    else if (idx == operands.size())
        return target == cur_target;
    bool found = false;
    for (int i = 0; !found && i < 3; i++) {
        long long new_target = cur_target;
        if (i == 0) {
            new_target *= operands[idx];
        } else if (i == 1) {
            new_target += operands[idx];
        } else {
            new_target = stoll(to_string(cur_target) + to_string(operands[idx]));
        }
        found = isPossible(operands, target, idx + 1, new_target);
    }
    return found;
}

int main() {
    long long result = 0;
    string line;
    while (getline(cin, line)) {
        int semi_colon_idx = line.find(":");
        long long target = stoll(line.substr(0, semi_colon_idx));
        stringstream ss(line.substr(semi_colon_idx + 1, line.size() - semi_colon_idx - 1));
        vector<long long> operands;
        long long temp;
        while (ss >> temp) operands.emplace_back(temp);
        result += isPossible(operands, target, 1, operands[0]) ? target : 0;
    }
    cout << result << endl;
}
