#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

struct element {
    long long src, dest, range;
};

vector<long long> convertToVector(string &input) {
    stringstream ss(input);
    vector<long long> result;
    long long n;
    while (ss >> n) {
        result.push_back(n);
    }
    return result;
}

void readElementds(vector<element> &elements) {
    string line;
    getline(cin, line); // ignore
    while (getline(cin, line)) {
        if (line == "") break;
        vector<long long> values = convertToVector(line);
        element e;
        e.src = values[1];
        e.dest = values[0];
        e.range = values[2];
        elements.push_back(e);
    }
}

long long getValue(const vector<element> &source, long long key) {
    for (auto e : source) {
        if (key >= e.src && key < e.src + e.range) return e.dest + (key - e.src);
    }
    return key;
}

int main() {
    freopen("in.txt", "r", stdin);
    vector<long long> seeds;
    vector<element> seed_to_soil;
    vector<element> soil_to_fertilizer;
    vector<element> fertilizer_to_water;
    vector<element> water_to_light;
    vector<element> light_to_temperature;
    vector<element> temperature_to_humidity;
    vector<element> humidity_to_location;

    string line;
    getline(cin, line);
    line = line.substr(line.find(':') + 1, line.size() - line.find(':') - 1);
    seeds = convertToVector(line);

    getline(cin, line);
    readElementds(seed_to_soil);
    readElementds(soil_to_fertilizer);
    readElementds(fertilizer_to_water);
    readElementds(water_to_light);
    readElementds(light_to_temperature);
    readElementds(temperature_to_humidity);
    readElementds(humidity_to_location);

    long long result = 1e15;
    for (auto seed : seeds) {
        long long soil = getValue(seed_to_soil, seed);
        long long fertilizer = getValue(soil_to_fertilizer, soil);
        long long water = getValue(fertilizer_to_water, fertilizer);
        long long light = getValue(water_to_light, water);
        long long temperature = getValue(light_to_temperature, light);
        long long humidity = getValue(temperature_to_humidity, temperature);
        long long location = getValue(humidity_to_location, humidity);
        result = min(result, location);
    }

    cout << result << endl;
}
