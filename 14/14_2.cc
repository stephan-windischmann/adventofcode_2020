#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <utility>
#include <vector>

#define INPUT "input" 

struct prog {
    std::string mask;
    std::vector<std::pair<unsigned long, std::bitset<36>> > mem;
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
            std::pair<unsigned long, std::bitset<36> > memItem;
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

void getMemAddr(const std::bitset<36> &memAddr, const std::string &mask, \
        std::set<unsigned long> &addrs) {
    if (std::count(mask.begin(), mask.end(), 'X') == 0) {
        addrs.insert(memAddr.to_ulong());
        return;
    }
    
    int i = mask.find_first_of('X');
    std::string newMask = mask;
    newMask[i] = '0';
    std::bitset<36> bitSet0 = memAddr;
    bitSet0[i] = false;
    std::bitset<36> bitSet1 = memAddr;
    bitSet1[i] = true;
    getMemAddr(bitSet0, newMask, addrs);
    getMemAddr(bitSet1, newMask, addrs);
}

void loadMem(const std::string &mask, \
        const std::pair<unsigned long, std::bitset<36> > &memItem, \
        std::map<unsigned long, unsigned long> &mem) {
    
    std::set<unsigned long> addrs;
    std::bitset<36> memAddr(memItem.first);
    // Loop through memAddr and set bit to 1 where mask is 1.
    for (int i = 0; i < mask.size(); ++i) {
        if (mask[i] == '1') {
            memAddr[i] = true;
        }
    }
    getMemAddr(memAddr, mask, addrs);

    unsigned long val = memItem.second.to_ulong();
    for (auto const& addr : addrs) {
        mem[addr] = val;
    }
}

void runProg(const std::vector<prog> &input, std::map<unsigned long, unsigned long> &mem) {
    for (auto const& progItem : input) {
        for (auto const& memItem : progItem.mem) {
            loadMem(progItem.mask, memItem, mem);
        }
    }
}

int main() {
    std::vector<prog> input;
    loadInput(input);

    std::map<unsigned long, unsigned long> mem;

    runProg(input, mem);

    unsigned long sumMem = 0;

    for (auto const& item : mem) {
        sumMem += item.second;
    }
    
    std::cout << "Sum of all values in memory: " << sumMem << std::endl;

    return 0;
}

