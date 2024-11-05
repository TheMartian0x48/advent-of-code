#include <iostream>
#include <map>
#include <string>
#include <vector>


using namespace std;


int main() {
    freopen("in.txt", "r", stdin );
    string line;
    int result = 0;

    map<string, int> expectedCubes = {{"red", 12}, {"green", 13}, {"blue", 14}};

    while (getline(cin, line)) {
        int start = 0;
        int end = line.find(':');
        string game = line.substr(start, end - start);
        string data = line.substr(end + 1, line.size());
        int id = stoi(game.substr(game.find(' ') + 1, game.size()));

        start = 0;
        vector<string> subsets = vector<string>();
        while((end = data.find(';', start)) != -1) {
            subsets.push_back(data.substr(start, end - start));
            start = end + 1;
        }
        subsets.push_back(data.substr(start, data.size() - start));
        bool is_valid_game = true;
        for (auto &subset : subsets) {
            start = 1;
            do {
                end = subset.find(',', start);
                int safe_end = end == -1 ? subset.size() : end;
                int space_idx = subset.find(' ', start);
                int balls = stoi(subset.substr(start, space_idx));
                string color = subset.substr(space_idx + 1, safe_end - space_idx - 1);
                is_valid_game = balls <= expectedCubes[color];
                start = end + 2;
            } while (is_valid_game && end != -1);

            if (!is_valid_game) break;
        }
        if (is_valid_game)
            result += id;
    }
    cout << result ;
}
