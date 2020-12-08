#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input"
#define TYPE "shiny gold"

struct bagType {
    int count;
    std::string type;
};

void loadInput(std::vector<std::string> &input) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }

    file.close();
}

std::vector<bagType> parseContent(const std::string &content) {
    std::vector<bagType> res;
    
    if (content[0] == 'n') {
        return res;
    }

    std::stringstream ss(content);
    
    std::string s;
    while (std::getline(ss, s, ',')) {
        std::regex e ("\\s*(\\d+)\\s+([a-z]+\\s+[a-z]+).*");
        std::smatch sm;
        std::regex_match(s.cbegin(), s.cend(), sm, e);
       
        bagType dp {std::stoi(sm[1]), sm[2]};
        res.push_back(dp);
    }

    return res;
}

void parseInput(const std::vector<std::string> &input, \
        std::map<std::string, std::vector<bagType> > &contains) {

    for (auto const& line : input) {
        std::regex e ("([a-z]+\\s+[a-z]+)\\s+[a-z]+\\s+contain\\s+(.*)");
        std::smatch sm;
        std::regex_match(line.begin(), line.end(), sm, e);
        std::string type = sm[1];
        std::vector<bagType> contained = parseContent(sm[2]);
        contains[type] = contained;
    }
}

// Perform a DFS
int getNumBags(std::string type,
        std::map<std::string, std::vector<bagType> > contains) {
    int res = 1;
    
    for (auto const& bt : contains[type]) {
        res += bt.count * getNumBags(bt.type, contains);
    }

    return res;
}

int main() {
    std::vector<std::string> input;
    std::map<std::string, std::vector<bagType> > contains;

    loadInput(input);
    parseInput(input, contains);
    
    int numBags = getNumBags(TYPE, contains) - 1;

    std::cout << TYPE <<" bags contain: " << numBags << " other bags." << std::endl;

    return 0;
}
