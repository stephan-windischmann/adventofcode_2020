#include <fstream>
#include <iostream>
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

int stepCountTrees(int curX, int curY, int stepsR, int stepsD, \
        const std::vector<std::string> &input, int trees) {

    // Check if we reached the end.
    if (curY == input.size()) {
        return trees;
    }

    // Check if we went past the limit of the line.
    if (curX >= input[curY].size()) {
        curX = curX - input[curY].size();
    }

    // Check if current pos is a tree
    if (input[curY][curX] == '#') {
        ++trees;
    }
    
    return stepCountTrees(curX + stepsR, curY + stepsD, \
            stepsR, stepsD, input, trees);
}

int main() {
    std::vector<std::string> input;

    loadInput(input);

    int numTrees = stepCountTrees(0, 0, 3, 1, input, 0);

    std::cout << "Num trees: " << numTrees << std::endl;

    return 0;
}
