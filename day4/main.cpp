#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
}

std::vector<std::vector<char>> load_data(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return {};
    }

    std::vector<std::vector<char>> data;
    std::string line;

    while (std::getline(input_file, line)) {
        size_t line_size = line.size();
        std::vector<char> row(line_size);

        for(size_t i = 0; i < line_size; ++i) {
            row[i] = line[i];
        }

        data.push_back(row);
    }

    return data;
}

bool get_xmas(size_t i, size_t j, size_t m, size_t n, std::string phrase, const std::vector<std::vector<char>>& data, std::pair<int, int> dir) {
    while(i < m && j < n && phrase.size() < 4) {
        phrase += data[i][j];
        i += dir.first;
        j += dir.second;
    }
    return phrase == "XMAS";
}

bool get_x_mas(size_t i, size_t j, size_t m, size_t n, const std::vector<std::vector<char>>& data) {
    if (i == 0 || i + 1 >= m || j == 0 || j + 1 >= n || data[i][j] != 'A') {
        return false;
    }

    auto check_mas = [](char c1, char c2) {
        return (c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M');
    };

    char down_right = data[i + 1][j + 1];
    char up_left    = data[i - 1][j - 1];
    if (!check_mas(down_right, up_left)) {
        return false;
    }

    char down_left = data[i + 1][j - 1];
    char up_right  = data[i - 1][j + 1];
    return check_mas(down_left, up_right);
}

void part1(const std::string& path_to_input) {
    auto data                                   = load_data(path_to_input);
    size_t m                                    = data.size();
    size_t n                                    = data[0].size();
    int xmas_count                              = 0;
    std::vector<std::pair<int, int>> directions = {
        {0, 1},   // right
        {0, -1},  // left
        {1, 0},   // down
        {-1, 0},  // up
        {1, 1},   // down-right
        {-1, -1}, // up-left
        {1, -1},  // down-left
        {-1, 1}   // up-right
    };

    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < n; ++j) {
            if(data[i][j] == 'X') {
                for(auto const& dir : directions) xmas_count += get_xmas(i, j, m , n, "", data, dir);
            }
        }
    }

    std::cout << "Xmas count: " << xmas_count << std::endl;
}

void part2(const std::string& path_to_input) {
    auto data       = load_data(path_to_input);
    size_t m        = data.size();
    size_t n        = data[0].size();
    int x_mas_count = 0;

    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < n; ++j) {
            if(data[i][j] == 'A') {
                x_mas_count += get_x_mas(i, j,m , n, data);
            }
        }
    }
    std::cout << "X-mas count: " << x_mas_count << std::endl;
}


int main() {
    part1(INPUT_FILE_NAME);
    part2(INPUT_FILE_NAME);
    return 0;
} 