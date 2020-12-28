#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

#define INPUT "input"

enum Operator {ADD, MULT};

void loadInput(std::vector<std::string> &input) {
    std::ifstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }

    file.close();
}

long calcLine(const std::string &line, int &i) {
    std::stack<long> s;
    Operator op;
    while (i < line.size()) {
        long curNum = 0;
        bool num = false;
        char c = line[i++];
        if (c == ' ') {
            continue;
        }
        if (c == '(') {
            curNum = calcLine(line, i);
            num = true;
        }
        if (c >= '0' && c <= '9') {
            while (c >= '0' && c <= '9') {
                curNum = (c - '0') + curNum * 10;
                c = line[i++];
            }
            num = true;
        }
        if (num) {
            if (s.size() == 0) {
                s.push(curNum);
            } else {
                long prev = s.top();
                s.pop();
                if (op == ADD) {
                    s.push(prev + curNum);
                } else {
                    s.push(prev * curNum);

                }
            }
        }
        if (c == '+') {
            op = ADD;
            continue;
        }
        if (c == '*') {
            op = MULT;
            continue;
        }
        if (c == ')') {
            break;
        }
    }
    return s.top();
}

long getSum(const std::vector<std::string> &input) {
    long sum = 0;

    for (auto const& line : input) {
        int i = 0;
        sum += calcLine(line, i);
    }

    return sum;
}

int main() {
    std::vector<std::string> input;
    loadInput(input);

    long sum = getSum(input);
    std::cout << "Result: " << sum << std::endl;

    return 0;
}

