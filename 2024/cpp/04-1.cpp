#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

// 2024 | DAY 4 | PART 1

int main() {
    vector<string> gr;
    string line;
    // ifstream data("in.txt");
    ifstream data("test.txt");
    while (data >> line) gr.push_back(line);
    int result = 0;

    const string XMAS = "XMAS";
    vector<int> dy{0, -1, -1, -1, 0, 1, 1, 1}, dx{-1, -1, 0, 1, 1, 1, 0, -1};

    for (int i = 0; i < gr.size(); i++) {
        for (int j = 0; j < gr[i].size(); j++) {
            for (int k = 0; k < 8; k++) {
                bool found = true;
                for (int step = 0; found && step < 4; step++) {
                    int r = i + step * dy[k];
                    int c = j + step * dx[k];
                    found = r >= 0 && r < gr.size() && c >= 0 && c < gr[0].size() && gr[r][c] == XMAS[step];
                }
                result += found;
            }
        }
    }
    cout << result << "\n";
}
