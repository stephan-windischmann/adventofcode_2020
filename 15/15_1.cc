#include <fstream>
#include <iostream>
#include <map>
#include <utility>

#define INPUT  "input"

void loadInput(std::map<int, std::pair<int, int> > &input, \
        int &turn, int &lastNum) {
    std::ifstream file;
    file.open(INPUT);

    std::string in;
    turn = 1;
    while (std::getline(file, in, ',')) {
        int cur = std::stoi(in);
        input[cur] = std::pair<int, int>{turn, turn};
        lastNum = cur;
        ++turn;
    }

    file.close();
}

int playGame(int finalTurn, int &turn, int &lastNum, \
        std::map<int, std::pair<int, int> > &input) {
    while (turn <= finalTurn) {
        int newNum = input[lastNum].second - input[lastNum].first;

        if (input.find(newNum) == input.end()) {
            input[newNum] = std::pair<int, int>{turn, turn};
        } else {
            input[newNum].first = input[newNum].second;
            input[newNum].second = turn;
        }
        
        lastNum = newNum;
        ++turn;
    }

    return lastNum;
}

int main() {
    std::map<int, std::pair<int, int> > input;
    int turn;
    int lastNum;
    
    loadInput(input, turn, lastNum);

    int res = playGame(2020, turn, lastNum, input);

    std::cout << "Result: " << res << std::endl;

    return 0;
}

