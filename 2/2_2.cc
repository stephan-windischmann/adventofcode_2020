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

bool isValidPass(std::string const &pass, char c, int posA, int posB) {
    if ((pass[posA] == c && pass[posB] != c) || \
            (pass[posA] != c && pass[posB] == c)) {
        return true;
    }
    return false;
}

int getValidPass(std::vector<std::string> const &input) {
    int valid = 0;

    for (auto const& line : input) {
        std::stringstream ss(line);

        int posA, posB;
        char c;
        char skip;
        std::string pass;

        ss >> posA;
        ss >> skip;
        ss >> posB;
        ss >> c;
        ss >> skip;
        ss >> pass;
        
        if (isValidPass(pass, c, posA - 1, posB - 1)) {
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
