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

struct ret {
    bool suc;
    int acc;
};

inst getInst(const std::string &op) {
    std::regex e("([a-z]+)\\s([-+]\\d+)");
    std::smatch sm;
    std::regex_match(op.begin(), op.end(), sm, e);

    return inst {sm[1], std::stoi(sm[2])};
}

void loadInput(std::vector<inst> &input) {
    std::ifstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        inst curInst = getInst(line);
        input.push_back(curInst);
    }

    file.close();
}

ret runCode(std::vector<inst> &input) {
    int acc = 0;
    
    int *ran = new int[input.size()] ();
    
    int i = 0;
    while (i < input.size()) {
        inst curInst = input[i];
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
     
    return ret {i == input.size(), acc};
}

int fixCode(std::vector<inst> &input) {
    ret retVal;

    // Brute force approach. Replace one instruction and try.
    for (auto &curInst : input) {
        if (curInst.op == "acc") {
            continue;
        }
        if (curInst.op == "nop" && curInst.step == 0) {
            continue;
        }
        if (curInst.op == "nop") {
            curInst.op = "jmp";
        } else {
            curInst.op = "nop";
        }
        retVal = runCode(input);
        if (retVal.suc) {
            break;
        }
        if (curInst.op == "nop") {
            curInst.op = "jmp";
        } else {
            curInst.op = "nop";
        }
    }

    return retVal.acc;
}

int main() {
    std::vector<inst> input;

    loadInput(input);

    int acc = fixCode(input);

    std::cout << "Acc value: " << acc << std::endl;

    return 0;
}

