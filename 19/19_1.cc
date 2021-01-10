#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

#define INPUT "input"

std::string lstrip(std::string s) {
    const auto sNewBegin = s.find_first_not_of(" ");
    const int sLen = s.size() - sNewBegin;
    return s.substr(sNewBegin, sLen);
}

void loadInput(std::map<int, std::string> &rules, \
    std::vector<std::string> &msg) {
    std::ifstream file;

    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        if (line == "") {
            break;
        }

        std::stringstream ss(line);
        
        std::string ruleNum;
        std::getline(ss, ruleNum, ':');
        std::string ruleCont;
        std::getline(ss, ruleCont, ':');

        rules[std::stoi(ruleNum)] = lstrip(ruleCont);
    }
    while (std::getline(file, line)) {
        msg.push_back(line);
    }

    file.close();
}

std::string parseRules(std::map<int, std::string> &rules, int rN, \
    std::map<int, std::string> &memo) {
    if (memo.find(rN) != memo.end()) {
        return memo[rN];
    }
    
    std::string rule = rules[rN];

    if (rule == "\"a\"") {
        memo[rN] = "a";
        return "a";
    } else if (rule == "\"b\"") {
        memo[rN] = "b";
        return "b";    
    }

    std::string res = "(";
    std::stringstream ss(rule);

    std::string opt;
    while (std::getline(ss, opt, '|')) {
        res += "(";
        std::stringstream rs(opt);
        int r;
        while (rs >> r) {
            res += parseRules(rules, r, memo);
        }
        res += ")|";
    }
    if (res[res.size() - 1] == '|') {
        res = res.substr(0, res.size() - 1);
    }
    res += ")";
    memo[rN] = res;
    return res;
}

int countInvalidMsg(std::map<int, std::string> &rules, \
    const std::vector<std::string> &msg) {
    int res = 0;

    std::map<int, std::string> memo;
    std::string regexRule = parseRules(rules, 0, memo);
    std::regex re(regexRule);

    for (auto const& m : msg) {
        if (std::regex_match(m, re)) {
            ++res;
        }
    }

    return res;
}

int main() {
    std::map<int, std::string> rules;
    std::vector<std::string> msg;
    loadInput(rules, msg);

    int res = countInvalidMsg(rules, msg);
    std::cout << "Valid Messages: " << res << std::endl;

    return 0;
}
