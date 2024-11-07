#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> readVector() {
    string line;
    getline(cin, line);
    int idx = line.find(':');
    line = line.substr(idx + 1, line.size() - idx - 1);
    vector<int> result;
    stringstream ss(line);
    while (ss >> idx) result.push_back(idx);
    return result;
}

int main() {
    vector<int> time = readVector();
    vector<int> dis = readVector();

    // extremum + binary search
    // f = (T - x) * x
    // f' = T - 2x
    int result = 1;

    for (int i = 0; i < dis.size(); i++) {
        int ans = 0;
        int t = time[i], d = dis[i];

        if (t & 1) {
            int x = t / 2;
            int max_d = (t - x) * x;
            if (max_d > d) {
                int l = 0, r = x;
                while (l + 1 < r) {
                    int m = (l + r) >> 1;
                    if ((t - m) * m <= d)
                        l = m;
                    else
                        r = m;
                }
                ans += x - l;
            }
            x++;
            max_d = (t - x) * x;
            if (max_d > d) {
                int l = x, r = t + 1;
                while (l + 1 < r) {
                    int m = (l + r) >> 1;
                    if ((t - m) * m <= d)
                        r = m;
                    else
                        l = m;
                }
                ans += r - x;
            }
        } else {
            int x = t / 2;
            int max_d = (t - x) * x;
            if (max_d <= d) continue;
            int l = 0, r = x;
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if ((t - m) * m <= d) {
                    l = m;
                } else
                    r = m;
            }
            ans += x - l;
            l = x, r = t + 1;
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if ((t - m) * m <= d) {
                    r = m;
                } else
                    l = m;
            }
            ans += r - x - 1;
        }
        cout << ans << endl;
        result *= ans;
    }

    cout << result << endl;
}
