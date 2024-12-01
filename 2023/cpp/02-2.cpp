#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> extractSubsets(const string &line) {
    auto result = vector<string>();
    int start = 0, end = -1;
    while ((end = line.find(';', start)) != -1) {
        result.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    result.push_back(line.substr(start, line.size() - start));
    return result;
}

int gamePoint(const vector<string> &subsets) {
    int red = 0, green = 0, blue = 0;
    for (auto &subset : subsets) {
        int start = 1, end = 0;
        do {
            end = subset.find(',', start);
            int safe_end = end == -1 ? subset.size() : end;
            int space_idx = subset.find(' ', start);
            int balls = stoi(subset.substr(start, space_idx));
            string color = subset.substr(space_idx + 1, safe_end - space_idx - 1);
            start = end + 2;

            if (color == "red")
                red = max(red, balls);
            else if (color == "green")
                green = max(green, balls);
            else if (color == "blue")
                blue = max(blue, balls);
        } while (end != -1);
    }
    return red * green * blue;
}

int main() {
    string line;
    int result = 0;

    while (getline(cin, line)) {
        int start = 0;
        int end = line.find(':');
        string game = line.substr(start, end - start);
        string data = line.substr(end + 1, line.size());
        int id = stoi(game.substr(game.find(' ') + 1, game.size()));

        vector<string> subsets = extractSubsets(data);
        result += gamePoint(subsets);
    }
    cout << result;
}
