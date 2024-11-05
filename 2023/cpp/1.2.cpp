#include <iostream>
#include <vector>

using namespace std;


int main() {
    vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string line;
    int result = 0;
    while (getline(cin, line)) {
        int len = line.size();
        int first = -1, last = -1;
        for (int i = 0; i < len; i++) {
            char ch = line[i];
            bool is_digit = ch >= '0' && ch <= '9';
            if (is_digit) {
                last = ch - '0';
                if (first == -1) first = ch - '0';
                continue;
            }

            for (int n = 1; n <= 9; n++) {
                const string & number = numbers[n - 1];
                int n_len = number.size();
                bool is_start_of_number = true;
                for (int pos = 0; pos < n_len; pos++) {
                    bool is_match = i + pos < len && line[i + pos] == number[pos];
                    if (!is_match) {
                        is_start_of_number = false;
                        break;
                    }
                }
                if (is_start_of_number) {
                    if (first == -1) first = n;
                    last = n;
                    break;
                }
            }
        }
        result += 10 * first + last;
    }
    cout << result;
}
