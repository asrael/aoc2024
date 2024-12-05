#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool safe_levels(vector<int>& levels) {
    for (size_t i = 1; i < levels.size() - 1; i++) {
        int diff1 = levels[i] - levels[i - 1];
        int diff2 = levels[i + 1] - levels[i];
        bool signChange = (diff1 > 0 && diff2 < 0) || (diff1 < 0 && diff2 > 0);
        bool notWithinLimits = !diff1 || !diff2 || abs(diff1) > 3 || abs(diff2) > 3;

        if (signChange || notWithinLimits) {
            return false;
        }
    }

    return true;
}

void part1() {
    fstream file("input.txt");
    string line;
    int num_safe = 0;

    while (getline(file, line)) {
        int level;
        vector<int> levels;
        istringstream iss(line);

        while (iss >> level) {
            levels.push_back(level);
        }

        if (safe_levels(levels)) {
            num_safe++;
        }
    }

    cout << num_safe << endl;
}

void part2() {
    fstream file("input.txt");
    string line;
    int num_safe = 0;

    while (getline(file, line)) {
        int level;
        vector<int> levels;
        istringstream iss(line);

        while (iss >> level) {
            levels.push_back(level);
        }

        if (safe_levels(levels)) {
            num_safe++;
        } else {
            for (size_t i = 0; i < levels.size(); i++) {
                vector<int> temp = levels;

                temp.erase(temp.begin() + i);

                if (safe_levels(temp)) {
                    num_safe++;
                    break;
                }
            }
        }
    }

    cout << num_safe << endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    part1();
    part2();

    return 0;
}
