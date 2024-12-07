#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

        int n = operands.size();
        bool found = false;
        for (int i = 0; !found && i < (1 << (n - 1)); i++) {
            long long cur_target = operands[0];
            for (int j = 1; j < n; j++) {
                int k = (n - 1) - j;
                if (i & (1 << k))
                    cur_target += operands[j];
                else cur_target *= operands[j];
            }
            found = target == cur_target;
        }
        result += found ? target : 0;
    }
    cout << result << endl;
}

