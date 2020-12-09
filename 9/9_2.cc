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

long findWeakness(std::vector<long> &input, long firstNum) {
    // Use a rolling window
    int beg = 0, end = 0;
    
    long sum = input[0];

    for (int i = beg + 1; i < input.size(); ++i) {
        ++end;
        sum += input[i];
        while (sum > firstNum && beg < end) {
            sum -= input[beg];
            ++beg;
        }
        if (sum == firstNum) {
            break;
        }
    }
    
    int min = input[beg];
    int max = input[beg];
    for (int i = beg + 1; i <= end; ++i) {
        if (input[i] < min) {
            min = input[i];
        }
        if (input[i] > max) {
            max = input[i];
        }
    }
    
    return min + max;
}

int main() {
    std::vector<long> input;

    loadInput(input);

    long firstNum = findFirst(input, 25);
    long weakness = findWeakness(input, firstNum);
    std::cout << "Encryption weakness: " << weakness << std::endl;

    return 0;
}

