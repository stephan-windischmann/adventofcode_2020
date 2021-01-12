#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#define INPUT "input"

std::string lstrip(std::string s) {
    const auto sNewBegin = s.find_first_not_of(" ");
    const int sLen = s.size() - sNewBegin;
    return s.substr(sNewBegin, sLen);
}

void loadInput(std::map<std::string, std::vector<std::string> > &input,
    std::map<std::string, int> &ingrCount) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        std::regex e("(.*)\\(contains (.*)\\)");
        std::smatch sm;
        std::regex_match(line, sm, e);
        std::string ingrs = sm[1];
        std::string ingr;
        std::stringstream ingr_stream(ingrs);
        while (ingr_stream >> ingr) {
            if (ingrCount.find(ingr) == ingrCount.end()) {
                ingrCount[ingr] = 1;
            } else {
                ++ingrCount[ingr];
            }
        }
        std::stringstream alergens(sm[2]);
        std::string alergen;
        while (std::getline(alergens, alergen, ',')) {
            input[lstrip(alergen)].push_back(ingrs);
        }
    }

    file.close();
}

void makeSet(const std::string &str, std::set<std::string> &s) {
    std::stringstream ss(str);
    std::string cur;
    while (ss >> cur) {
        s.insert(cur);
    }
}

std::string solve(const std::map<std::string, std::vector<std::string> > &input,
    std::map<std::string, int> &ingrCount) {
    
    std::map<std::string, std::set<std::string> > hasAlrgn;

    for (auto const &alrg : input) {
        std::set<std::string> isSet;
        makeSet(alrg.second[0], isSet);
        std::set<std::string> notSet;
        for (int i = 1; i < alrg.second.size(); ++i) {
            std::set<std::string> cur;
            makeSet(alrg.second[i], cur);
            std::set<std::string> isTemp = isSet;
            isSet.clear();
            std::set_intersection(isTemp.begin(), isTemp.end(), 
                cur.begin(), cur.end(), std::inserter(isSet, isSet.end()));
        }
        hasAlrgn[alrg.first] = isSet;
    }

    std::set<std::string> found;
    while(found.size() < input.size()) {
        for (auto &alrg : hasAlrgn) {
            if (alrg.second.size() == 1) {
                if (found.find(*alrg.second.begin()) == found.end()) {
                    found.insert(*alrg.second.begin());
                }
            } else {
                for (auto const &i : found) {
                    if (alrg.second.find(i) != alrg.second.end()) {
                        alrg.second.erase(i);
                    }
                }
            }
        }
    }

    std::vector<std::string> alrgnIngr;
    for (auto const &alrgn : hasAlrgn) {
        alrgnIngr.push_back(*alrgn.second.begin());
    }

    std::stringstream res;
    for (auto ii = alrgnIngr.begin(); ii != alrgnIngr.end(); ++ii) {
        res << *ii;
        if (ii != alrgnIngr.end() - 1) {
            res << ',';
        }
    }

    return res.str();
}

int main() {
    std::map<std::string, std::vector<std::string> > input; 
    std::map<std::string, int> ingrCount;
    loadInput(input, ingrCount);

    std::string res = solve(input, ingrCount);
    std::cout << "Solution: " << res << std::endl;

    return 0;
}
