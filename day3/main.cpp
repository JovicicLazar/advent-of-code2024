#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "types.hpp"

namespace {
    const std::string INPUT_FILE_NAME = "puzzle_input.txt";
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
            num1 = 0;
            num2 = 0;
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
            }
            break;
        
        case States::COMMA:
            if(isdigit(ch)) {
                num2 = (num2 * 10) + (ch - '0');
                curr_state = States::NUM2;
            } else {
                curr_state = States::START;
            }
            break;
        
        case States::NUM2:
            if(isdigit(ch)) {
                num2 = (num2 * 10) + (ch - '0');
            } else if(ch == ')') {
                sum += num1 * num2;
                curr_state = States::START;
            } else {
                curr_state = States::START;
            }
            break;
        }
    }

    std::cout << sum << std::endl;
}

void part2(const std::string& path_to_input) {
    const std::string corrupted = load_data(path_to_input);
    if (corrupted.empty()) {
        std::cout << 0 << std::endl;
        return;
    }

    StatesWithChecks curr_state = StatesWithChecks::START;
    GlobalStates global_state   = GlobalStates::UNKNOWN;
    int sum                     = 0;
    int num1                    = 0;
    int num2                    = 0;
    bool add_to_sum             = true;

    for (size_t i = 0; i < corrupted.size(); ++i) {
        const char ch = corrupted[i];

        switch (curr_state) {
        case StatesWithChecks::START:
            num1 = 0;
            num2 = 0;
            global_state = GlobalStates::UNKNOWN;
            if (ch == 'm') {
                curr_state = StatesWithChecks::HAS_M;
            } else if (ch == 'd') {
                curr_state = StatesWithChecks::HAS_D;
            }
            break;

        case StatesWithChecks::HAS_M:
            global_state = GlobalStates::MAKE_MUL;
            curr_state = (ch == 'u') ? StatesWithChecks::HAS_U :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_U:
            curr_state = (ch == 'l') ? StatesWithChecks::HAS_L :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_L:
            curr_state = (ch == '(') ? StatesWithChecks::OPENBR :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_D:
            global_state = GlobalStates::MAKE_DO;
            curr_state = (ch == 'o') ? StatesWithChecks::HAS_O :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_O:
            if (ch == '(') {
                curr_state = StatesWithChecks::OPENBR;
            } else if (ch == 'n') {
                curr_state = StatesWithChecks::HAS_N;
                global_state = GlobalStates::MAKE_DONT;
            } else {
                curr_state = (ch == 'm') ? StatesWithChecks::HAS_M :
                             (ch == 'd') ? StatesWithChecks::HAS_D :
                             StatesWithChecks::START;
            }
            break;

        case StatesWithChecks::HAS_N:
            curr_state = (ch == '\'') ? StatesWithChecks::HAS_SQ :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_SQ:
            curr_state = (ch == 't') ? StatesWithChecks::HAS_T :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::HAS_T:
            curr_state = (ch == '(') ? StatesWithChecks::OPENBR :
                         (ch == 'm') ? StatesWithChecks::HAS_M :
                         (ch == 'd') ? StatesWithChecks::HAS_D :
                         StatesWithChecks::START;
            break;

        case StatesWithChecks::OPENBR:
            if (global_state == GlobalStates::MAKE_MUL && isdigit(ch)) {
                num1 = num1 * 10 + (ch - '0');
                curr_state = StatesWithChecks::NUM1;
            } else if ((global_state == GlobalStates::MAKE_DO || global_state == GlobalStates::MAKE_DONT) && ch == ')') {
                add_to_sum = (global_state == GlobalStates::MAKE_DONT) ? false : true;
                curr_state = StatesWithChecks::START;
            } else {
                curr_state = (ch == 'm') ? StatesWithChecks::HAS_M :
                             (ch == 'd') ? StatesWithChecks::HAS_D :
                             StatesWithChecks::START;
            }
            break;

        case StatesWithChecks::NUM1:
            if (isdigit(ch)) {
                num1 = num1 * 10 + (ch - '0');
            } else if (ch == ',') {
                curr_state = StatesWithChecks::COMMA;
            } else {
                curr_state = (ch == 'm') ? StatesWithChecks::HAS_M :
                             (ch == 'd') ? StatesWithChecks::HAS_D :
                             StatesWithChecks::START;
                num1 = 0;
            }
            break;

        case StatesWithChecks::COMMA:
            if (isdigit(ch)) {
                num2 = num2 * 10 + (ch - '0');
                curr_state = StatesWithChecks::NUM2;
            } else {
                curr_state = (ch == 'm') ? StatesWithChecks::HAS_M :
                             (ch == 'd') ? StatesWithChecks::HAS_D :
                             StatesWithChecks::START;
                num1 = 0;
            }
            break;

        case StatesWithChecks::NUM2:
            if (isdigit(ch)) {
                num2 = num2 * 10 + (ch - '0');
            } else if (ch == ')') {
                if(add_to_sum) sum += num1 * num2;
                curr_state = StatesWithChecks::START;
            } else {
                curr_state = (ch == 'm') ? StatesWithChecks::HAS_M :
                             (ch == 'd') ? StatesWithChecks::HAS_D :
                             StatesWithChecks::START;
                num1 = 0;
                num2 = 0;
            }
            break;
        }
    }

    std::cout << sum << std::endl;
} 

int main() {
    part1(INPUT_FILE_NAME);
    part2(INPUT_FILE_NAME);
    return 0;
} 