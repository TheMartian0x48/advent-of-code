#include <iostream>
#include <map>
#include <string>
#include <vector>


using namespace std;


int main() {
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
        int red = 0, green = 0, blue = 0;
        for (auto &subset : subsets) {
            start = 1;
            do {
                end = subset.find(',', start);
                int safe_end = end == -1 ? subset.size() : end;
                int space_idx = subset.find(' ', start);
                int balls = stoi(subset.substr(start, space_idx));
                string color = subset.substr(space_idx + 1, safe_end - space_idx - 1);
                start = end + 2;

                if (color == "red") red = max(red, balls);
                else if (color == "green") green = max(green, balls);
                else if (color == "blue") blue  = max(blue, balls);
            } while (end != -1);
        }
        result += red * green * blue;
    }
    cout << result ;
}
