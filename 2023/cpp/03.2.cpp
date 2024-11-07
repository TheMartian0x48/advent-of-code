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

int numberEndIdx(const string &s, int cur) {
    while (cur < s.size() && isdigit(s[cur])) cur++;
    return cur - 1;
}

int main() {
    std::vector<string> engine = std::vector<string>();

    string input;
    while (getline(cin, input)) {
        engine.push_back(input);
    }

    using ll = long long;
    ll result = 0;

    vector<int> dxs = {-1, -1, 0, 1, 1, 1, 0, -1};
    vector<int> dys = {0, -1, -1, -1, 0, 1, 1, 1};
    vector<int> dy = {-1, 1};

    int rows = engine.size();
    int cols = engine[0].size();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            char ch = engine[row][col];
            if (ch != '*') continue;
            vector<int> parts;

            if (col > 0 && isdigit(engine[row][col - 1])) {
                long long v = getPartValue(engine, row, col - 1);
                if (v) parts.push_back(v);
            }
            if (col + 1 < cols && isdigit(engine[row][col + 1])) {
                long long v = getPartValue(engine, row, col + 1);
                if (v) parts.push_back(v);
            }

            // check top row
            if (row > 0) {
                int r = row - 1;
                if (col > 0 && isdigit(engine[r][col - 1])) {
                    int idx = numberEndIdx(engine[r], col - 1);
                    long long v = getPartValue(engine, r, col - 1);
                    if (v) parts.push_back(v);
                    if (idx < col && col + 1 < cols && isdigit(engine[r][col + 1])) {
                        v = getPartValue(engine, r, col + 1);
                        if (v) parts.push_back(v);
                    }
                } else if (isdigit(engine[r][col])) {
                    long long v = getPartValue(engine, r, col);
                    if (v) parts.push_back(v);
                } else if (col + 1 < cols && isdigit(engine[r][col + 1])) {
                    long long v = getPartValue(engine, r, col + 1);
                    if (v) parts.push_back(v);
                }
            }

            // check bottom row
            if (row + 1 < rows) {
                int r = row + 1;
                if (col > 0 && isdigit(engine[r][col - 1])) {
                    int idx = numberEndIdx(engine[r], col - 1);
                    long long v = getPartValue(engine, r, col - 1);
                    if (v) parts.push_back(v);
                    if (idx < col && col + 1 < cols && isdigit(engine[r][col + 1])) {
                        v = getPartValue(engine, r, col + 1);
                        if (v) parts.push_back(v);
                    }
                } else if (isdigit(engine[r][col])) {
                    long long v = getPartValue(engine, r, col);
                    if (v) parts.push_back(v);
                } else if (col + 1 < cols && isdigit(engine[r][col + 1])) {
                    long long v = getPartValue(engine, r, col + 1);
                    if (v) parts.push_back(v);
                }
            }

            if (parts.size() == 2) {
                result += parts[0] * parts[1];
            }
        }
    }

    cout << result << endl;
}
