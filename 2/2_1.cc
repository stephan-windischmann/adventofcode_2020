#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<std::string> &input) {
    std::ifstream file;
    file.open(INPUT);

    std::string line;

    while (getline(file, line)) {
        input.push_back(line);
    }
}

bool isValidPass(std::string const &pass, char c, int min, int max) {
    int count = 0;

    for (auto curChar : pass) {
        if (curChar == c) {
            ++count;
        }
    }

    return count >= min && count <= max;
}

int getValidPass(std::vector<std::string> const &input) {
    int valid = 0;

    for (auto const& line : input) {
        std::stringstream ss(line);

        int min, max;
        char c;
        char skip;
        std::string pass;

        ss >> min;
        ss >> skip;
        ss >> max;
        ss >> c;
        ss >> skip;
        ss >> pass;

        if (isValidPass(pass, c, min, max)) {
            ++valid;
        }
    }

    return valid;
}

int main() {
    std::vector<std::string> input;

    loadInput(input);
    
    int numValidPass = getValidPass(input);
    
    std::cout << "Valid passwords: " << numValidPass << std::endl;

    return 0;
}
