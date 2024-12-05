#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

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

        bool is_valid = true;
        for (int i = 1; is_valid && i < pages.size(); i++) {
            is_valid = rules.count(to_string(pages[i - 1]) + "|" + to_string(pages[i]));
        }
        if (is_valid) result += pages[pages.size() / 2];
    }
    cout << result << endl;
}
