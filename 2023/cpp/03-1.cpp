#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

bool isSymbol(char ch) {
    return ch != '.' && !isdigit(ch);
}

long long getPartValue(const vector<string> &engine, int row, int col) {
    int rows = engine.size(), cols = engine[0].size();
    auto &line = engine[row];
    int start = col, end = col;
    while (start >= 0 && isdigit(line[start])) start--;
    while (end < cols && isdigit(line[end])) end++;
    start++, end--;
    long long result = stoll(line.substr(start, end - start + 1));
    for (int i = start; i <= end; i++) {
        if (row > 0 && isSymbol(engine[row - 1][i])) return result;
        if (row + 1 < rows && isSymbol(engine[row + 1][i])) return result;
    }
    if (start > 0) {
        if (isSymbol(engine[row][start - 1])) return result;
        if (row > 0 && isSymbol(engine[row - 1][start - 1])) return result;
        if (row + 1 < rows && isSymbol(engine[row + 1][start - 1])) return result;
    }

    if (end + 1 < cols) {
        if (isSymbol(engine[row][end + 1])) return result;
        if (row > 0 && isSymbol(engine[row - 1][end + 1])) return result;
        if (row + 1 < rows && isSymbol(engine[row + 1][end + 1])) return result;
    }
    return 0;
}

int main() {
    std::vector<string> engine = std::vector<string>();

    string input;
    while (getline(cin, input)) {
        engine.push_back(input);
    }

    using ll = long long;
    ll result = 0;

    for (int row = 0; row < engine.size(); row++) {
        auto &line = engine[row];
        int cols = line.size();
        int col = 0;
        while (col < cols) {
            if (isdigit(line[col])) {
                result += getPartValue(engine, row, col);
                while (col < cols && isdigit(line[col])) col++;
            } else {
                col++;
            }
        }
    }

    cout << result << endl;
}
