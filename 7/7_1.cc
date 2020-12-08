#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input"
#define TYPE "shiny gold"

void loadInput(std::vector<std::string> &input) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }

    file.close();
}

std::vector<std::string> parseContent(const std::string &content) {
    std::vector<std::string> res;
    
    if (content[0] == 'n') {
        return res;
    }

    std::stringstream ss(content);
    
    std::string s;
    while (std::getline(ss, s, ',')) {
        std::regex e ("\\s*\\d+\\s+([a-z]+\\s+[a-z]+).*");
        std::smatch sm;
        std::regex_match(s.cbegin(), s.cend(), sm, e);
        res.push_back(sm[1]);
    }

    return res;
}

void parseInput(const std::vector<std::string> &input, \
        std::map<std::string, std::vector<std::string> > &isContained) {

    for (auto const& line : input) {
        std::regex e ("([a-z]+\\s+[a-z]+)\\s+[a-z]+\\s+contain\\s+(.*)");
        std::smatch sm;
        std::regex_match(line.begin(), line.end(), sm, e);
        std::string type = sm[1];
        std::vector<std::string> parents = parseContent(sm[2]);
        isContained[type] = parents;
    }
}

int getNumBags(std::string type,
        const std::map<std::string, std::vector<std::string> > &isContained) {
    int res = 0;

    std::queue<std::string> q;

    std::vector<std::string> cur = isContained[type];

    for (auto const& s : cur) {
        q.push(s);
    } 

    return res;
}

int main() {
    std::vector<std::string> input;
    std::map<std::string, std::vector<std::string> > isContained;

    loadInput(input);
    parseInput(input, isContained);
    
    int numBags = getNumBags(TYPE, isContained);

    std::cout << "Bags containing " << TYPE << ": " << numBags << std::endl;

    return 0;
}
