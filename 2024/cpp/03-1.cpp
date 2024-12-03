#include <cctype>
#include <iostream>

using namespace std;

long long mul(const string &input) {
    long long result = 0;
    int pcur = 0, ccur = 0;

    bool is_mul = false;
    bool comma_count = 0;
    while (ccur < input.size()) {
        if (input[ccur] == '(') {
            is_mul = ccur >= 3 && input[ccur - 3] == 'm' && input[ccur - 2] == 'u' && input[ccur - 1] == 'l';
            pcur = ccur + 1;
            comma_count = 0;
        } else if (input[ccur] == ')') {
            if (is_mul) {
                int comma = input.find(',', pcur);
                is_mul = comma > pcur && comma < ccur;
                if (is_mul) {
                    cout << input.substr(pcur - 4, ccur - pcur + 4 + 1) << endl;
                    long long a = stoll(input.substr(pcur, comma - pcur));
                    long long b = stoll(input.substr(comma + 1, ccur - comma - 1));
                    cout << a << " * " << b << " = " << (a * b) << "\n";
                    result += a * b;
                }
            }
            is_mul = false;
            comma_count = 0;
        } else if (is_mul) {
            is_mul = input[ccur] == ',' || isdigit(input[ccur]);
            comma_count = is_mul ? comma_count + input[ccur] == ',' : 0;
        }
        ccur++;
    }
    return result;
}

int main() {
    string input;
    long long result = 0;
    while (cin >> input) result += mul(input);
    cout << result << "\n";
}
