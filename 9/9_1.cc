#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<long> &input) {
    std::ifstream file;
    file.open(INPUT);

    long cur;
    while (file >> cur) {
        input.push_back(cur);
    }

    file.close();
}

long findFirst(std::vector<long> &input, int preamble) {
    long i = 0;

    std::set<long> curSet;

    for (;i < preamble; ++i) {
        curSet.insert(input[i]);
    }

    for (;i < input.size(); ++i) {
        long want = input[i];
        bool found = false;
        for (long j = i - preamble; j < i; ++j) {
            if ((want - input[j] != input[j]) && \
                    (curSet.find(want - input[j]) != curSet.end())) {
                found = true;
            }
        }
        if (!found) {
            return want;
        }
        curSet.erase(input[i - preamble]);
        curSet.insert(input[i]);
    }


    return -1;
}

int main() {
    std::vector<long> input;

    loadInput(input);

    long firstNum = findFirst(input, 25);

    std::cout << "First not sum number: " << firstNum << std::endl;

    return 0;
}

