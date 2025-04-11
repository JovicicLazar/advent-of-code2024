#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
    const size_t REPORT_NUMBER        = 1000;

    enum States {
        START,
        HAS_M,
        HAS_U,
        HAS_L,
        OPENB,
        NUM1,
        COMMA,
        NUM2
    };
}

std::string load_data(const std::string& path_to_input) {
    std::ifstream input_file(path_to_input);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << path_to_input << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << input_file.rdbuf();  
    std::string memory = buffer.str(); 

    return memory;
}

void part1(const std::string& path_to_input) {
    const std::string corrupted = load_data(path_to_input);
    States curr_state           = States::START;
    int sum                     = 0;
    int num1                    = 0;
    int num2                    = 0;

    for(size_t i = 0; i < corrupted.size(); ++i) {
        const char ch = corrupted[i];

        switch (curr_state)
        {
        case States::START:
            if(ch == 'm') curr_state = States::HAS_M;
            break;
        
        case States::HAS_M:
            curr_state = (ch == 'u') ? States::HAS_U : States::START;
            break;
        
        case States::HAS_U:
            curr_state = (ch == 'l') ? States::HAS_L : States::START;
            break;
        
        case States::HAS_L:
            curr_state = (ch == '(') ? States::OPENB : States::START;
            break;

        case States::OPENB:
            if(isdigit(ch)) {
                num1 = (num1 * 10) + (ch - '0');
                curr_state = States::NUM1;
            } else {
                curr_state = States::START;
            }
            break;

        case States::NUM1:
            if(isdigit(ch)) {
                num1 = (num1 * 10) + (ch - '0');
            } else if(ch == ',') {
                curr_state = States::COMMA;
            } else {
                curr_state = States::START;
                num1 = 0;
            }
            break;
        
        case States::COMMA:
            if(isdigit(ch)) {
                num2 = (num2 * 10) + (ch - '0');
                curr_state = States::NUM2;
            } else {
                curr_state = States::START;
                num1 = 0;
            }
            break;
        
        case States::NUM2:
            if(isdigit(ch)) {
                num2 = (num2 * 10) + (ch - '0');
            } else if(ch == ')') {
                sum += num1 * num2;
                num1 = 0;
                num2 = 0;
                curr_state = States::START;
            } else {
                curr_state = States::START;
                num1 = 0;
                num2 = 0;
            }
            break;

        default:
            break;
        }
    }

    std::cout << sum << std::endl;
}


int main() {
    part1(INPUT_FILE_NAME);
    return 0;
} 