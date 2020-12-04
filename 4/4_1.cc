#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
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

void parseInput(std::vector<std::string> &input, \
        std::vector<std::map<std::string, std::string>> &data) {
    int i = 0;
    while (i < input.size()) {
        std::map<std::string, std::string> in;
        
        while (input[i] != "") {
            std::stringstream ss(input[i]);
            std::string pair;
            while (ss >> pair) {
                std::stringstream ssPair(pair);
                std::string key;
                std::string val;
                std::getline(ssPair, key, ':');
                std::getline(ssPair, val, ':');
                in[key] = val;
            }
            ++i;
        }

        data.push_back(in);
        ++i;
    }
}

int countValidPassport(std::vector<std::map<std::string, std::string>> data) {
    int res = 0;
    
    for (auto const& pp : data) {
        if ((pp.size() == 8) || (pp.size() == 7 && pp.find("cid") == pp.end())) {
            ++res;
        }
    }

    return res;
}

int main() {
    std::vector<std::string> input;
    std::vector<std::map<std::string, std::string>> data;
   
    loadInput(input);
    parseInput(input, data);

    int validPassport = countValidPassport(data);

    std::cout << "Valid passport: " << validPassport << std::endl;

    return 0;
}
