#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

void part1() {
    fstream file("input.txt");
    regex pattern(R"(mul\((\d+),\s*(\d+)\))");
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    auto words_begin = sregex_iterator(text.begin(), text.end(), pattern);
    auto words_end = sregex_iterator();

    int result = 0;

    for (sregex_iterator iter = words_begin; iter != words_end; iter++) {
        smatch match = *iter;
        int num1 = stoi(match[1].str());
        int num2 = stoi(match[2].str());

        result += num1 * num2;
    }

    cout << result << endl;
}

void part2() {
    fstream file("input.txt");
    regex pattern(R"(mul\((\d+),\s*(\d+)\)|do\(\)|don[']t\(\))");
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    auto words_begin = sregex_iterator(text.begin(), text.end(), pattern);
    auto words_end = sregex_iterator();

    bool enabled = true;
    int result = 0;

    for (sregex_iterator iter = words_begin; iter != words_end; iter++) {
        smatch match = *iter;
        if (enabled && match.size() > 2 && match[1].matched && match[2].matched) {
            int num1 = stoi(match[1].str());
            int num2 = stoi(match[2].str());
            result += num1 * num2;
        } else if (match.str() == "do()") {
            enabled = true;
        } else if (match.str() == "don't()") {
            enabled = false;
        }
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
