#include <iostream>
#include <set>
#include <vector>

using namespace std;

vector<int> DX{-1, 0, 1, 0}, DY{0, -1, 0, 1};

void countTrailHeads(const vector<string> &gr, int r, int c, char target, set<int> &heads) {
    if (gr[r][c] == '9') {
        heads.insert(r * 1000 + c);
    }
    for (int i = 0; i < 4; i++) {
        int rr = r + DY[i], cc = c + DX[i];
        if (rr >= 0 && rr < gr.size() && cc >= 0 && cc < gr[0].size() && gr[rr][cc] == target + 1) {
            countTrailHeads(gr, rr, cc, gr[rr][cc], heads);
        }
    }
}

int main() {
    vector<string> gr;
    string line;
    while (cin >> line) gr.emplace_back(line);

    int result = 0;
    for (int r = 0; r < gr.size(); r++) {
        for (int c = 0; c < gr[0].size(); c++) {
            if (gr[r][c] == '0') {
                set<int> st;
                countTrailHeads(gr, r, c, '0', st);
                result += st.size();
            }
        }
    }
    cout << result << endl;
}
