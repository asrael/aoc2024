#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<char>> get_input() {
    fstream file("input.txt");
    string line;
    vector<vector<char>> input;

    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        input.push_back(row);
    }

    return input;
}

bool exited(int x, int y, int rows, int cols) {
    return x < 0 || y < 0 || x >= cols || y >= rows;
}

struct point_dir {
    int x, y;
    char dir;

    bool operator==(const point_dir& other) const {
        return x == other.x && y == other.y && dir == other.dir;
    }
};

struct point_dir_h {
    size_t operator()(const point_dir& p) const {
        return hash<int>{}(p.x) ^ hash<int>{}(p.y) ^ hash<char>{}(p.dir);
    }
};

void traverse_map(unordered_set<point_dir, point_dir_h>& loop, vector<vector<char>>& map,
                  int x, int y, char dir) {
    int dx = 0;
    int dy = 0;

    switch (dir) {
        case 'N': dy = -1; break;
        case 'S': dy = 1; break;
        case 'E': dx = 1; break;
        case 'W': dx = -1; break;
    }

    point_dir p = {x, y, dir};

    if (!loop.contains(p)) {
        loop.insert(p);
    } else {
        map.clear();
        return;
    }

    map[y][x] = 'X';

    if (exited(x + dx, y + dy, map.size(), map[0].size())) {
        return;
    }

    if (map[y + dy][x + dx] != '#') {
        traverse_map(loop, map, x + dx, y + dy, dir);
    } else {
        switch (dir) {
            case 'N': dir = 'E'; break;
            case 'S': dir = 'W'; break;
            case 'E': dir = 'S'; break;
            case 'W': dir = 'N'; break;
        }
        traverse_map(loop, map, x, y, dir);
    }
}

int part1() {
    unordered_set<point_dir, point_dir_h> loop;
    vector<vector<char>> map = get_input();
    int rows = map.size();
    int cols = map[0].size();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == '^') {
                traverse_map(loop, map, x, y, 'N');
                break;
            }
        }
    }

    if (!map.size()) {
        return 0;
    }

    int sum = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == 'X') {
                sum++;
            }
        }
    }

    return sum;
}

int part2() {
    vector<pair<int, int>> walls;
    vector<vector<char>> map = get_input();
    pair<int, int> start;
    int rows = map.size();
    int cols = map[0].size();
    int sum = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == '^') {
                start = {x, y};
            }

            if (map[y][x] == '.') {
                walls.emplace_back(x, y);
            }
        }
    }

    auto [start_x, start_y] = start;
    for (const auto& wall : walls) {
        unordered_set<point_dir, point_dir_h> loop;
        vector<vector<char>> new_map = map;
        auto [x, y] = wall;

        new_map[y][x] = '#';

        traverse_map(loop, new_map, start_x, start_y, 'N');

        if (!new_map.size()) {
            sum++;
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    cout << part1() << endl;
    cout << part2() << endl;

    return 0;
}
