#include <iostream>
#include <string>

using namespace std;


int main() {
    string line;
    int result = 0;
    while (getline(cin, line)) {
        int s = -1, e = -1;
        for (auto &ch : line) {
            bool is_digit = ch >= '0' && ch <= '9';
            if (is_digit && s == -1) s = ch - '0';
            if (is_digit) e = ch - '0';
        }
        result += 10 * s + e;
    }
    cout << result;
}
