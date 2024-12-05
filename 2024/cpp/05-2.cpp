#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool isValid(const vector<int> &pages, const set<string> &rules) {
    bool is_valid = true;
    for (int i = 1; is_valid && i < pages.size(); i++) {
        string t = to_string(pages[i - 1]) + "|" + to_string(pages[i]);
        is_valid = rules.count(t);
    }
    return is_valid;
}

int main() {
    set<string> rules;
    string line;

    int result = 0;
    while (getline(cin, line) && line != "") rules.insert(line);

    while (getline(cin, line)) {
        stringstream ss(line);
        string temp;
        vector<int> pages;
        while (getline(ss, temp, ',')) pages.emplace_back(stoi(temp));
        if (isValid(pages, rules)) continue;
        int n = pages.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                string r = to_string(pages[i]) + "|" + to_string(pages[j]);
                if (!rules.count(r)) swap(pages[i], pages[j]);
            }
        }
        result += pages[n / 2];
    }
    cout << result << endl;
}
