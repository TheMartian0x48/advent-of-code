#include <cctype>
#include <iostream>
#include <string>

using namespace std;

long long calculateMul(const string &section, int pcur, int ccur) {
    if (pcur < 3 || "mul" != section.substr(pcur - 3, 3)) return 0;
    int i = pcur + 1;
    while (section[i] != ',' && i < ccur) {
        if (isdigit(section[i]))
            i++;
        else
            return 0;
    }
    int comma = i++;
    while (i < ccur) {
        if (isdigit(section[i]))
            i++;
        else
            return 0;
    }
    if (comma + 1 >= ccur || pcur + 1 >= comma) return 0;
    long long a = stoll(section.substr(pcur + 1, comma - pcur - 1));
    long long b = stoll(section.substr(comma + 1, ccur - comma - 1));
    return a * b;
}

long long solve(const string &section) {
    int len = section.size();
    int ccur = 0, pcur = 0;
    long long result = 0;
    bool is_disabled = false;
    while (ccur < len) {
        while (ccur < len && section[ccur] != ')') {
            if (section[ccur] == '(') pcur = ccur;
            ccur++;
        }
        if (ccur == len) break;
        if (ccur > 0 && section[ccur - 1] == '(' && section[ccur] == ')') {
            bool enabling = pcur >= 2 && "do" == section.substr(pcur - 2, 2);
            bool disabling = !enabling && pcur >= 5 && "don't" == section.substr(pcur - 5, 5);
            if (is_disabled)
                is_disabled = !enabling;
            else
                is_disabled = disabling;
        } else {
            result += is_disabled ? 0ll : calculateMul(section, pcur, ccur);
        }
        ccur++;
    }
    return result;
}

int main() {
    string input;
    long long result = 0;
    string sections; cin >> sections;
    while (cin >> input) sections += "\n" + input;
    result = solve(sections);
    cout << result << "\n";
}
