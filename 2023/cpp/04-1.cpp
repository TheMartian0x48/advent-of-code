#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

int matchCount(const string &line) {
    int start_idx = line.find(':');
    int end_idx = line.find('|');
    stringstream ss(line.substr(start_idx + 1, end_idx - start_idx - 1));
    auto winner_list = set<int>();
    int n;
    while (ss >> n) {
        winner_list.insert(n);
    }

    stringstream sss(line.substr(end_idx + 1, line.size() - end_idx - 1));
    vector<int> winner;
    while (sss >> n) {
        if (winner_list.count(n)) {
            winner.push_back(n);
        }
    }
    return winner.size();
}

int main() {
    string line;
    long long result = 0;
    while (getline(cin, line)) {
        int count = matchCount(line);
        if (count) result += pow(2, count - 1);
    }
    cout << result << "\n";
}
