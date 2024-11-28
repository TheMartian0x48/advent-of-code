#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<string> universe;
    string line;
    while (getline(cin, line)) universe.push_back(line);
    vector<long long> cols(universe[0].size(), 0);
    vector<long long> rows(universe.size(), 0);
    vector<int> rows_expands(universe.size(), true);
    vector<bool> cols_expands(universe[0].size(), true);

    for (int row = 0; row < universe.size(); row++) {
        for (int col = 0; col < universe[0].size(); col++) {
            rows_expands[row] = rows_expands[row] && universe[row][col] == '.';
        }
        rows[row] += rows_expands[row] ? 1000000 : 1;
        if (row) rows[row] += rows[row - 1];
    }

    for (int col = 0; col < universe[0].size(); col++) {
        for (int row = 0; row < universe.size(); row++) {
            cols_expands[col] = cols_expands[col] && universe[row][col] == '.';
        }
        cols[col] += cols_expands[col] ? 1000000 : 1;
        if (col) cols[col] += cols[col - 1];
    }

    vector<pair<int, int>> galaxies;
    for (int i = 0; i < universe.size(); i++) {
        for (int j = 0; j < universe[0].size(); j++) {
            if (universe[i][j] == '#') galaxies.push_back({i, j});
        }
    }
    long long result = 0;
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto gOne = galaxies[i];
            auto gTwo = galaxies[j];
            long long ans = 0;
            ans += abs(cols[gTwo.second] - cols[gOne.second]);
            ans += abs(rows[gTwo.first] - rows[gOne.first]);
            result += ans;
        }
    }
    cout << result << endl;
}
