#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> get_chars_from_input() {
    fstream file("input.txt");
    vector<vector<char>> chars;
    string line;

    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        chars.push_back(row);
    }

    return chars;
}

bool valid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

void part1() {
    vector<vector<char>> chars = get_chars_from_input();
    int dirs[8][2] = {
        {0, -1},  // up
        {1, 0},   // right
        {0, 1},   // down
        {-1, 0},  // left
        {-1, -1}, // up-left
        {1, -1},  // up-right
        {-1, 1},  // down-left
        {1, 1},   // down-right
    };
    int count = 0;
    int rows = chars.size();
    int cols = chars[0].size();
    string xmas = "XMAS";

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            for (int i = 0; i < 8; i++) {
                int dx = dirs[i][0];
                int dy = dirs[i][1];

                bool found = true;
                for (int j = 0; j < 4; j++) {
                    int new_x = r + j * dx;
                    int new_y = c + j * dy;

                    if (!valid(new_x, new_y, rows, cols) ||
                        chars[new_x][new_y] != xmas[j]) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    count++;
                }
            }
        }
    }

    cout << count << endl;
}

void part2() {
    vector<vector<char>> chars = get_chars_from_input();
    int count = 0;
    int rows = chars.size();
    int cols = chars[0].size();

    for (int r = 1; r < rows - 1; r++) {
        for (int c = 1; c < cols - 1; c++) {
            if (chars[r][c] == 'A') {
                if (valid(r - 1, c - 1, rows, cols) &&
                    valid(r + 1, c + 1, rows, cols)) {
                    if (chars[r - 1][c - 1] == 'M' &&
                        chars[r - 1][c + 1] == 'M' &&
                        chars[r + 1][c + 1] == 'S' &&
                        chars[r + 1][c - 1] == 'S') {
                        count++;
                    }
                    if (chars[r - 1][c - 1] == 'S' &&
                        chars[r - 1][c + 1] == 'S' &&
                        chars[r + 1][c + 1] == 'M' &&
                        chars[r + 1][c - 1] == 'M') {
                        count++;
                    }
                    if (chars[r - 1][c - 1] == 'S' &&
                        chars[r + 1][c - 1] == 'S' &&
                        chars[r - 1][c + 1] == 'M' &&
                        chars[r + 1][c + 1] == 'M') {
                        count++;
                    }
                    if (chars[r - 1][c - 1] == 'M' &&
                        chars[r + 1][c - 1] == 'M' &&
                        chars[r - 1][c + 1] == 'S' &&
                        chars[r + 1][c + 1] == 'S') {
                        count++;
                    }
                }
            }
        }
    }

    cout << count << endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    part1();
    part2();

    return 0;
}
