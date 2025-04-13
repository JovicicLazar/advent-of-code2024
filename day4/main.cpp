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

bool get_xmas(int i, int j, int m, int n, std::string phrase, const std::vector<std::vector<char>>& data, std::pair<int, int> dir) {
    while(i >= 0 && i < m && j >=0 && j <= n && phrase.size() < 4) {
        phrase += data[i][j];
        i += dir.first;
        j += dir.second;
    }
    std::cout << phrase << std::endl;
    return phrase == "XMAS";
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

    std::cout << xmas_count << std::endl;
}

int main() {
    part1(INPUT_FILE_NAME);
    return 0;
} 