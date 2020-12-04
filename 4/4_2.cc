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

void parseInput(const std::vector<std::string> &input, \
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

bool checkByr(const std::string &byr) {
    int byrI = std::stoi(byr);

    return byrI >= 1920 && byrI <= 2002;
}

bool checkIyr(const std::string &iyr) {
    int iyrI = std::stoi(iyr);

    return iyrI >= 2010 && iyrI <= 2020;
}

bool checkEyr(const std::string &eyr) {
    int eyrI = std::stoi(eyr);

    return eyrI >= 2020 && eyrI <= 2030;
}

bool checkHgt(const std::string &hgt) {
    std::stringstream ss(hgt);
    int height;
    std::string unit;
    ss >> height;
    ss >> unit;

    if (unit == "cm") {
        return height >= 150 && height <= 193;
    }
    else if (unit == "in") {
        return height >= 59 && height <= 76;
    }
    return false;
}

bool checkHcl(const std::string &hcl) {
    std::stringstream ss(hcl);
    char c;
    std::string s;
    ss >> c;
    ss >> s;
    
    if (c != '#') {
        return false;
    }
    
    if (s.size() != 6) {
        return false;
    }

    for (auto const& c : s) {
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')) {
            continue;
        }
        return false;
    }

    return true;
}

bool checkEcl(const std::string &ecl) {
    if (ecl == "amb") {
        return true;
    }
    if (ecl == "blu") {
        return true;
    }
    if (ecl == "brn") {
        return true;
    }
    if (ecl == "gry") {
        return true;
    }
    if (ecl == "grn") {
        return true;
    }
    if (ecl == "hzl") {
        return true;
    }
    if (ecl == "oth") {
        return true;
    }
    return false;
}

bool checkPid(const std::string &pid) {
    if (pid.size() != 9) {
        return false;
    }

    for (auto const& c : pid) {
        if (c >= '0' && c <= '9') {
            continue;
        }
        return false;
    }

    return true;
}

bool checkPassport(std::map<std::string, std::string> pp) {
    if (!checkByr(pp["byr"])) {
        return false;
    }
    if (!checkIyr(pp["iyr"])) {
        return false;
    }
    if (!checkEyr(pp["eyr"])) {
        return false;
    }
    if (!checkHgt(pp["hgt"])) {
        return false;
    }
    if (!checkHcl(pp["hcl"])) {
        return false;
    }
    if (!checkEcl(pp["ecl"])) {
        return false;
    }
    if (!checkPid(pp["pid"])) {
        return false;
    }

    return true;
}


int countValidPassport(const std::vector<std::map<std::string, std::string>> data) {
    int res = 0;
    
    for (auto const& pp : data) {
        if ((pp.size() == 8) || \
                (pp.size() == 7 && pp.find("cid") == pp.end())) {
            if (checkPassport(pp)) {
                ++res;
            }
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
