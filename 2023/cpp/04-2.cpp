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
    vector<string> cards;
    long long result = 0;
    while (getline(cin, line)) {
        cards.push_back(line);
    }
    vector<long long> counts(cards.size(), 1ll);
    for (int i = 0; i < cards.size(); i++) {
        const string &card = cards[i];
        int count = matchCount(card);
        for (int j = 1; j <= count && j + i < counts.size(); j++) {
            counts[j + i] += counts[i];
        }
        result += counts[i];
    }
    cout << result << "\n";
}
