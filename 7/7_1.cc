#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<std::string> &input) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }

    file.close();
}

void parseInput(const std::vector<std::string> input, \
        std::map<std::string, std::vector<std::string>> &isContained) {

    for (auto const& line : input) {
        std::cout << line << std::endl;
        std::string container;
        //auto const cont = std::regex("[a-z]+\\s+[a-z]+");
        std::regex e ("([a-z]+\\s+[a-z]+)(.*)");
        std::smatch sm;
        std::regex_match(line.begin(), line.end(), sm, e);
        container = sm[1];
    }

}

int main() {
    std::vector<std::string> input;
    std::map<std::string, std::vector<std::string>> isContained;

    loadInput(input);
    parseInput(input, isContained);


    return 0;
}
