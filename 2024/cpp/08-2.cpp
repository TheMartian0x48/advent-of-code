#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> gr;
    string line;
    while (cin >> line) gr.emplace_back(line);

    set<string> antinodes;
    map<char, vector<pair<int, int>>> antenna;
    for (int r = 0; r < gr.size(); r++) {
        for (int c = 0; c < gr[0].size(); c++) {
            char ch = gr[r][c];
            if (ch != '.') {
                auto it = antenna.find(ch);
                if (it == antenna.end()) {
                    antenna[ch] = {{r, c}};
                } else {
                    it->second.push_back({r, c});
                }
            }
        }
    }
    for (auto iter = antenna.begin(); iter != antenna.end(); iter++) {
        auto &antennas = iter->second;
        for (int i = 0; i < antennas.size(); i++) {
            for (int j = i + 1; j < antennas.size(); j++) {
                antinodes.insert(to_string(antennas[i].first) + "|" + to_string(antennas[i].second));
                antinodes.insert(to_string(antennas[j].first) + "|" + to_string(antennas[j].second));
                int dy = antennas[j].first - antennas[i].first;
                int dx = antennas[j].second - antennas[i].second;
                int nr = antennas[i].first - dy;
                int nc = antennas[i].second - dx;
                int step = 1;
                while (nr >= 0 && nc >= 0 && nr < gr.size() && nc < gr[0].size()) {
                    antinodes.insert(to_string(nr) + "|" + to_string(nc));
                    step++;
                    nr = antennas[i].first - step * dy;
                    nc = antennas[i].second - step * dx;
                }
                nr = antennas[j].first + dy;
                nc = antennas[j].second + dx;
                step = 1;
                while (nr >= 0 && nc >= 0 && nr < gr.size() && nc < gr[0].size()) {
                    antinodes.insert(to_string(nr) + "|" + to_string(nc));
                    step++;
                    nr = antennas[j].first + step * dy;
                    nc = antennas[j].second + step * dx;
                }
            }
        }
    }
    cout << antinodes.size() << endl;
}
