#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <utility>
#include <vector>

#define INPUT "input" 

struct prog {
    std::string mask;
    std::vector<std::pair<int, std::bitset<36>> > mem;
};

void loadInput(std::vector<prog> &input) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string line;
    std::getline(file, line);
    while (!file.eof()) {
        std::regex e ("mask = (\\w+)");
        std::smatch sm;
        std::regex_match(line.cbegin(), line.cend(), sm, e);
        
        prog curProg;
        curProg.mask = sm[1];
        // Reverse mask to iterate in same order as bitset.
        std::reverse(curProg.mask.begin(), curProg.mask.end());

        while (std::getline(file, line)) {
            if (line.substr(0, 3) != "mem") {
                break;;
            }
            std::pair<int, std::bitset<36> > memItem;
            std::regex e("mem\\[(\\d+)\\]\\s=\\s(\\d+)");
            std::smatch sm;
            std::regex_match(line.cbegin(), line.cend(), sm, e);

            memItem.first = std::stoi(sm[1]);
            memItem.second = std::bitset<36>(std::stoul(sm[2]));
            curProg.mem.push_back(memItem);
        }
        input.push_back(curProg);
    }    

    file.close();
}

unsigned long applyMask(std::bitset<36> num, const std::string &mask) {
    if (num.size() != mask.size()) {
        return num.to_ulong();
    }

    for (int i = mask.size() - 1; i >= 0; --i) {
        if (mask[i] != 'X') {
            num[i] = (bool)(mask[i] - '0');
        }
    }
    return num.to_ulong();
}

void runProg(const std::vector<prog> &input, std::map<int, unsigned long> &mem) {
    for (auto const& progItem : input) {
        for (auto const& memItem : progItem.mem) {
            mem[memItem.first] = applyMask(memItem.second, progItem.mask);
        }
    }
}

int main() {
    std::vector<prog> input;
    loadInput(input);

    std::map<int, unsigned long> mem;

    runProg(input, mem);

    unsigned long sumMem = 0;

    for (auto const& item : mem) {
        sumMem += item.second;
    }
    
    std::cout << "Sum of all values in memory: " << sumMem << std::endl;

    return 0;
}

