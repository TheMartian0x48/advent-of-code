#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum class Type {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

string typeString(Type type) {
    if (type == Type::FIVE_OF_A_KIND) return "FIVE_OF_A_KIND";
    if (type == Type::FOUR_OF_A_KIND) return "FOUR_OF_A_KIND";
    if (type == Type::FULL_HOUSE) return "FULL_HOUSE";
    if (type == Type::THREE_OF_A_KIND) return "THREE_OF_A_KIND";
    if (type == Type::TWO_PAIR) return "TWO_PAIR";
    if (type == Type::ONE_PAIR) return "ONE_PAIR";
    return "HIGH_CARD";
};

struct Hand {
    string cards;
    int bid;
    Type type;
};

map<char, int> mp = {{'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},  {'6', 5},  {'7', 6}, {'8', 7},
                     {'9', 8}, {'T', 9}, {'J', 0}, {'Q', 11}, {'K', 12}, {'A', 13}};

bool cmp_hand(const Hand &a, const Hand &b) {
    if (a.type != b.type) return a.type < b.type;
    for (int i = 0; i < 5; i++) {
        char ca = a.cards[i];
        char cb = b.cards[i];
        if (ca == cb) continue;
        return mp[ca] < mp[cb];
    }
    return false;
}

Type getTypeWithJocker(const string &cards) {
    vector<int> count(128, 0);
    for (auto ch : cards) {
        count[ch]++;
    }
    int two = 0, three = 0, four = 0, jocker = count['J'];
    if (jocker == 5 || jocker == 4) return Type::FIVE_OF_A_KIND;
    for (int i = '0'; i < 'Z'; i++) {
        if (i == 'J') continue;
        two += count[i] == 2;
        three += count[i] == 3;
        four += count[i] == 4;
    }
    if (jocker == 3) {
        return two == 1 ? Type::FIVE_OF_A_KIND : Type::FOUR_OF_A_KIND;
    } else if (jocker == 2) {
        if (three == 1) return Type::FIVE_OF_A_KIND;
        return two == 1 ? Type::FOUR_OF_A_KIND : Type::THREE_OF_A_KIND;
    }
    if (four == 1)
        return Type::FIVE_OF_A_KIND;
    else if (three == 1)
        return Type::FOUR_OF_A_KIND;
    else if (two == 2)
        return Type::FULL_HOUSE;
    return two == 1 ? Type::THREE_OF_A_KIND : Type::ONE_PAIR;
}

Type getTypeWithoutJocker(const string &cards) {
    vector<int> count(128, 0);
    for (auto ch : cards) {
        count[ch]++;
    }
    int two = 0, three = 0;
    for (int i = 0; i < 128; i++) {
        if (count[i] == 5)
            return Type::FIVE_OF_A_KIND;
        else if (count[i] == 4)
            return Type::FOUR_OF_A_KIND;
        else if (count[i] == 3)
            three++;
        else if (count[i] == 2)
            two++;
    }
    if (three == 1 && two == 1)
        return Type::FULL_HOUSE;
    else if (three == 1)
        return Type::THREE_OF_A_KIND;
    else if (two == 2)
        return Type::TWO_PAIR;
    else if (two == 1)
        return Type::ONE_PAIR;
    return Type::HIGH_CARD;
}

Type getType(const string &cards) {
    return cards.find('J') == -1 ? getTypeWithoutJocker(cards) : getTypeWithJocker(cards);
}

Hand readHand(const string &line) {
    int idx = line.find(' ');
    Hand hand;
    hand.cards = line.substr(0, idx);
    hand.bid = stoi(line.substr(idx, line.size() - idx));
    hand.type = getType(hand.cards);
    return hand;
}

int main() {
    vector<Hand> hands;
    string line;
    while (getline(cin, line)) hands.push_back(readHand(line));
    sort(hands.begin(), hands.end(), cmp_hand);
    long long result = 0;
    for (int i = 0; i < hands.size(); i++) {
        result += (i + 1) * hands[i].bid;
    }
    cout << result << endl;
}
