#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<string> universe;
    string line;
    while (getline(cin, line)) universe.push_back(line);
    vector<long long> cols_distance(universe[0].size(), 0);
    vector<long long> rows_distance(universe.size(), 0);

    for (int row = 0; row < universe.size(); row++) {
        bool does_expand = true;
        for (int col = 0; does_expand && col < universe[0].size(); col++) {
            does_expand = universe[row][col] == '.';
        }
        rows_distance[row] += does_expand ? 2 : 1;
        if (row) rows_distance[row] += rows_distance[row - 1];
    }

    for (int col = 0; col < universe[0].size(); col++) {
        bool does_expand = true;
        for (int row = 0; does_expand && row < universe.size(); row++) {
            does_expand = universe[row][col] == '.';
        }
        cols_distance[col] += does_expand ? 2 : 1;
        if (col) cols_distance[col] += cols_distance[col - 1];
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
            result += abs(cols_distance[gTwo.second] - cols_distance[gOne.second]);
            result += abs(rows_distance[gTwo.first] - rows_distance[gOne.first]);
        }
    }
    cout << result << endl;
}
