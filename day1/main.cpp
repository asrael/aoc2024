#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> get_matrix_from_input() {
    int a, b;
    vector<vector<int>> matrix;
    ifstream file("input.txt");

    if (!file) {
        cerr << "Error opening input file!" << endl;
        return matrix;
    }

    while (file >> a >> b) {
        matrix.push_back({a, b});
    }

    return matrix;
}

void part1() {
    vector<vector<int>> matrix = get_matrix_from_input();

    for (size_t c = 0; c < 2; c++) {
        vector<int> column;

        for (size_t r = 0; r < matrix.size(); r++) {
            column.push_back(matrix[r][c]);
        }

        sort(column.begin(), column.end(), less<int>());

        for (size_t r = 0; r < matrix.size(); r++) {
            matrix[r][c] = column[r];
        }
    }

    int total_distance = 0;
    for (size_t r = 0; r < matrix.size(); r++) {
        total_distance += abs(matrix[r][0] - matrix[r][1]);
    }

    cout << total_distance << endl;
}

void part2() {
    unordered_map<int, int> map;
    vector<vector<int>> matrix = get_matrix_from_input();

    for (const auto& row : matrix) {
        map[row[1]]++;
    }

    int similarity_score = 0;

    for (const auto& row : matrix) {
        int number = row[0];

        if (map.find(number) != map.end()) {
            similarity_score += number * map[number];
        }
    }

    cout << similarity_score << endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    part1();
    part2();

    return 0;
}
