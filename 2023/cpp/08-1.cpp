#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
    string name, left, right;
};

int main() {
    string line;
    getline(cin, line);

    string instruction = line;
    getline(cin, line);

    vector<Node> nodes;
    map<string, int> mp;
    while (getline(cin, line)) {
        int idx = line.find(' ');
        Node node{};
        node.name = line.substr(0, idx);

        idx = line.find('(');
        int idx2 = line.find(',');
        node.left = line.substr(idx + 1, idx2 - idx - 1);
        idx = line.find(')');
        node.right = line.substr(idx2 + 2, idx - idx2 - 2);
        nodes.push_back(node);
        mp[node.name] = mp.size();
    }

    int idx = 0, dis = 0, cur = mp["AAA"];
    while (true) {
        bool is_left = instruction[idx] == 'L';
        idx = (idx + 1) % instruction.size();
        auto &node = nodes[cur];
        if (node.name == "ZZZ") break;
        if (is_left) {
            cur = mp[node.left];
        } else {
            cur = mp[node.right];
        }
        dis++;
    }
    cout << dis << endl;
}
