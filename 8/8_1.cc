#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define INPUT "input"

struct inst {
    std::string op;
    int step;
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

inst getInst(const std::string &op) {
    std::regex e("([a-z]+)\\s([-+]\\d+)");
    std::smatch sm;
    std::regex_match(op.begin(), op.end(), sm, e);

    return inst{sm[1], std::stoi(sm[2])};
}

int runCode(std::vector<std::string> &input) {
    int acc = 0;
    
    int *ran = new int[input.size()];

    int i = 0;
    while (i < input.size()) {
        inst curInst = getInst(input[i]);
        ran[i] = 1;

        if (curInst.op == "acc") {
            acc += curInst.step;
            ++i;
        } else if (curInst.op == "jmp") {
            i += curInst.step;
        } else if (curInst.op == "nop") {
            ++i;
        }

        if (ran[i] == 1) {
            break;
        }
    }
    
    delete[] ran;
    return acc;
}

int main() {
    std::vector<std::string> input;

    loadInput(input);

    int acc = runCode(input);

    std::cout << "Acc value: " << acc << std::endl;

    return 0;
}

