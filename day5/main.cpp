#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Input {
    vector<pair<int, int>> pairs;
    vector<vector<int>> updates;
};

Input parse_input() {
    fstream file("input.txt");
    bool first_section = true;
    string line;
    vector<pair<int, int>> pairs;
    vector<vector<int>> updates;

    while (getline(file, line)) {
        if (line.empty()) {
            if (first_section) {
                first_section = false;
            }
            continue;
        }

        istringstream stream(line);

        if (first_section) {
            char delim = '|';
            int x, y;

            if (stream >> x >> delim >> y) {
                pairs.emplace_back(x, y);
            }
        } else {
            string page_num;
            vector<int> page_nums;

            while (getline(stream, page_num, ',')) {
                page_nums.push_back(stoi(page_num));
            }

            updates.push_back(page_nums);
        }
    }

    return {pairs, updates};
}

bool valid_update(const vector<pair<int, int>>& pairs, const vector<int>& update) {
    for (const auto& pair : pairs) {
        auto [x, y] = pair;
        auto itX = find(update.begin(), update.end(), x);
        auto itY = find(update.begin(), update.end(), y);

        if (itX != update.end() && itY != update.end() && itX > itY) {
            return false;
        }
    }

    return true;
}

vector<int> fix_update(const vector<pair<int, int>>& pairs, const vector<int>& update) {
    vector<int> fixed(update);

    sort(fixed.begin(), fixed.end(), [&](int a, int b) {
        for (const auto& pair : pairs) {
            if (pair.first == a && pair.second == b) {
                return -1;
            } else if (pair.first == a && pair.second == b) {
                return 1;
            }
        }

        return 0;
    });

    return fixed;
}

void part1() {
    int result = 0;
    auto [pairs, updates] = parse_input();
    vector<vector<int>> valid_updates;

    for (const auto& update : updates) {
        if (valid_update(pairs, update)) {
            valid_updates.push_back(update);
        }
    }

    for (const auto& valid_update : valid_updates) {
        result += valid_update[valid_update.size() / 2];
    }

    cout << result << endl;
}

void part2() {
    int result = 0;
    auto [pairs, updates] = parse_input();
    vector<vector<int>> valid_updates;

    for (auto& update : updates) {
        if (!valid_update(pairs, update)) {
            valid_updates.push_back(fix_update(pairs, update));
        }
    }

    for (const auto& valid_update : valid_updates) {
        result += valid_update[valid_update.size() / 2];
    }

    cout << result << endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    part1();
    part2();

    return 0;
}
