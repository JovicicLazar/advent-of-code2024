#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
}

std::vector<std::vector<int>> load_data(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return {{}};
    }

    std::vector<std::vector<int>> reports;
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
    int n        = report.size();
    bool is_incr = (report[0] < report[n - 1])? true : false;

    for(int i = 1; i < report.size(); ++i) {
        int diff = report[i] - report[i - 1]; 
        if(is_incr) {
            if( diff < 1 || diff > 3) {
                return false;
            }
        } else if(!is_incr) {
            if( diff > -1 || diff < -3) {
                return false;
            }
        }
    }
    return true;
}

void part1(const std::string& path_to_input) {
    auto reports     = load_data(path_to_input);
    int good_reports = 0;
    bool inc         = false;

    for(const std::vector<int>& report : reports) {
        if(is_good_report(report)) good_reports++;
    }

    std::cout << good_reports << std::endl;
}

int main() {
    part1(INPUT_FILE_NAME);
    return 0;
} 