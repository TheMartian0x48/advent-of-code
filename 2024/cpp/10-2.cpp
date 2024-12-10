#include <iostream>
#include <vector>

using namespace std;

vector<int> DX{-1, 0, 1, 0}, DY{0, -1, 0, 1};

int countTrailHeads(const vector<string> &gr, int r, int c, char target) {
    if (gr[r][c] == '9') {
        return 1;
    }
    int result = 0;
    for (int i = 0; i < 4; i++) {
        int rr = r + DY[i], cc = c + DX[i];
        if (rr >= 0 && rr < gr.size() && cc >= 0 && cc < gr[0].size() && gr[rr][cc] == target + 1) {
            result += countTrailHeads(gr, rr, cc, gr[rr][cc]);
        }
    }
    return result;
}

int main() {
    vector<string> gr;
    string line;
    while (cin >> line) gr.emplace_back(line);

    int result = 0;
    for (int r = 0; r < gr.size(); r++) {
        for (int c = 0; c < gr[0].size(); c++) {
            if (gr[r][c] == '0') {
                result += countTrailHeads(gr, r, c, '0');
            }
        }
    }
    cout << result << endl;
}
