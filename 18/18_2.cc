#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

#define INPUT "input"

enum tokenType {NUM, LPAREN, RPAREN, ADD, MULT, END};
enum Operator {OP_ADD, OP_MULT, OP_LPAREN, OP_RPAREN};

struct token {
    tokenType type;
    int value;
};

std::vector<token> parseLine(const std::string &line) {
    std::vector<token> tokens;

    int i = 0;
    while (i < line.size()) {
        char c = line[i++];
        if (c == ' ') {
            continue;
        } else if (c == '+') {
            tokens.push_back(token{ADD});
        } else if (c == '*') {
            tokens.push_back(token{MULT});
        } else if (c == '(') {
            tokens.push_back(token{LPAREN});
        } else if (c == ')') {
            tokens.push_back(token{RPAREN});
        } else if (c >= '0' && c <= '9') {
            int cur = 0;
            while (c >= '0' && c <= '9') {
                cur = (c - '0') + cur * 10;
                c = line[i++];
            }
            tokens.push_back(token{NUM, cur});
            if (c == ')') {
                tokens.push_back(token{RPAREN});
            }
        }
    }
    tokens.push_back(token{END});

    return tokens;
}

void loadInput(std::vector<std::vector<token> > &input) {
    std::ifstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(parseLine(line));
    }

    file.close();
}

long resolveStacks(std::stack<long> &nums, std::stack<Operator> &ops) {
    while (nums.size() > 1) {
        long b = nums.top();
        nums.pop();
        long a = nums.top();
        nums.pop();
        Operator op = ops.top();
        ops.pop();
        long c;
        if (op == OP_ADD) {
            c = a + b;
        } else {
            c = a * b;
        }
        nums.push(c);
    }
    long top = nums.top();
    nums.pop();
    return top;
}

long calcLine(const std::vector<token> &line, int &i) {
    std::stack<long> nums;
    std::stack<Operator> ops;

    while (i < line.size()) {
        token curToken = line[i++];

        if (curToken.type == NUM) {
            nums.push(curToken.value);
        } else if (curToken.type == ADD) {
            ops.push(OP_ADD);
        } else if (curToken.type == MULT) {
            if (nums.size() == 1 || ops.top() == OP_MULT) {
                ops.push(OP_MULT);
            } else {
                long lval = resolveStacks(nums, ops);
                nums.push(lval);
                ops.push(OP_MULT);
            }
        } else if (curToken.type == LPAREN) {
            long rval = calcLine(line, i);
            nums.push(rval);
        } else if (curToken.type == RPAREN) {
            break;
        }
    }

    return resolveStacks(nums, ops);
}

long getSum(const std::vector<std::vector<token> > &input) {
    long sum = 0;

    for (auto const& line : input) {
        int i = 0;
        sum += calcLine(line, i);
    }

    return sum;
}

int main() {
    std::vector<std::vector<token> > input;
    loadInput(input);

    long sum = getSum(input);
    std::cout << "Result: " << sum << std::endl;

    return 0;
}

