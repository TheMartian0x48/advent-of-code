#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

/**
 * 1 2 3
 * 4 5 6
 * 7 8 9
 */

// 2024 | DAY 4 | PART 1

int main() {
    vector<string> gr;
    string line;
    ifstream data("in.txt");
    // ifstream data("test.txt");
    while (data >> line) gr.push_back(line);
    int result = 0;

    set<string> possibilites{"MSSM", "MMSS", "SSMM", "SMMS"};

    vector<int> dy{-1, -1, 1, 1}, dx{-1, 1, 1, -1};

    for (int i = 0; i < gr.size(); i++) {
        for (int j = 0; j < gr[i].size(); j++) {
            if (gr[i][j] != 'A') continue;
            string combination = "";
            for (int step = 0; step < 4; step++) {
                int r = i + dy[step];
                int c = j + dx[step];
                if (r >= 0 && r < gr.size() && c >= 0 && c < gr[0].size()) {
                    combination += gr[r][c];
                } else
                    break;
                result += possibilites.count(combination);
            }
        }
    }
    cout << result << "\n";
}
