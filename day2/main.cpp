#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
    const size_t REPORT_NUMBER        = 1000;
}

std::vector<std::vector<int>> load_data(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return {};
    }

    std::vector<std::vector<int>> reports;
    reports.reserve(REPORT_NUMBER);
    std::string line;

    while (std::getline(input_file, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int num;
    
        while (iss >> num) {
            numbers.push_back(num);
        }

        reports.push_back(numbers);
    }

    return reports;
}

bool is_good_report(const std::vector<int>& report) {
    const bool is_increasing         = report.front() < report.back();
    const auto& [min_diff, max_diff] = is_increasing ? std::make_pair(1, 3) : std::make_pair(-3, -1);

    for (size_t i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1];
        if (diff < min_diff || diff > max_diff) {
            return false;
        }
    }
    return true;
}

bool is_good_report_with_dampener(const std::vector<int>& report) {
    if (is_good_report(report)) return true;
    
    if (report.size() < 3) return true;

    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> temp;
        temp.reserve(report.size() - 1);
        
        for (size_t j = 0; j < report.size(); ++j) {
            if (j != i) {
                temp.push_back(report[j]);
            }
        }
        
        if (is_good_report(temp)) {
            return true;
        }
    }
    return false;
}

void part1(const std::string& path_to_input) {
    auto reports     = load_data(path_to_input);
    int good_reports = 0;

    for(const std::vector<int>& report : reports) {
        good_reports += is_good_report(report);
    }

    std::cout << good_reports << std::endl;
}

void part2(const std::string& path_to_input) {
    auto reports     = load_data(path_to_input);
    int good_reports = 0;

    for(std::vector<int>& report : reports) {
        good_reports += is_good_report_with_dampener(report);
    }

    std::cout << good_reports << std::endl;
}


int main() {
    part1(INPUT_FILE_NAME);
    part2(INPUT_FILE_NAME);
    return 0;
} 