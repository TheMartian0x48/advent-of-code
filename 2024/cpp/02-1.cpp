#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool is_safe(const vector<int> &report) {
  bool isSafe = true;
  int baseDiff = report[1] - report[0];
  for (int i = 1; isSafe && i < report.size(); i++) {
    int diff = report[i] - report[i - 1];
    isSafe = abs(diff) <= 3 && (diff * baseDiff) > 0;
  }
  return isSafe;
}

int main() {
  int result = 0;
  vector<int> report;
  string line;
  while (getline(cin, line)) {

    report.clear();
    stringstream ss(line);
    int level;
    while (ss >> level)
      report.push_back(level);
    result += is_safe(report);
  }
  cout << result << endl;
}
