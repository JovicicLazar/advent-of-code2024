#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
    const int LINE_COUNT              = 1000;
}

void part1(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return;
    }

    std::priority_queue<int, std::vector<int>> list1;
    std::priority_queue<int, std::vector<int>> list2;
    std::string line;
    int distance = 0;

    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        int num1, num2;

        iss >> num1 >> num2; 

        list1.push(num1);
        list2.push(num2);
    }

    while(!list1.empty()) {
        distance += std::abs((list1.top() - list2.top()));
        list1.pop();
        list2.pop();
    }

    std::cout << "Distance is: " << distance << std::endl;
}

void part2(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return;
    }

    std::unordered_map<int, int> right_freqs;
    std::vector<int> left_list(LINE_COUNT);
    int line_count = 0;
    std::string line;
    int similarity = 0;

    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        int num1, num2;

        iss >> num1 >> num2;

        right_freqs[num2]++;
        left_list[line_count] = num1;
        ++line_count;
    }

    for(int i = 0; i < LINE_COUNT; ++i) {
        similarity += left_list[i] * right_freqs[left_list[i]];
    }

    std::cout << "Similarity is: " << similarity << std::endl;
}

int main() {
    part1(INPUT_FILE_NAME);
    part2(INPUT_FILE_NAME);
    return 0;
} 