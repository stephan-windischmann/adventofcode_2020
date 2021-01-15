#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<std::string> &input) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }
    file.close();
}

void moveE(std::pair<int, int> &curPos) {
    ++curPos.first;
}

void moveW(std::pair<int, int> &curPos) {
    --curPos.first;
}

void moveNE(std::pair<int, int> &curPos) {
    if (curPos.second % 2 != 0) {
        ++curPos.first;
    }
    ++curPos.second;
}

void moveNW(std::pair<int, int> &curPos) {
    if (curPos.second % 2 == 0) {
        --curPos.first;
    }
    ++curPos.second;
}

void moveSE(std::pair<int, int> &curPos) {
    if (curPos.second % 2 != 0) {
        ++curPos.first;
    }
    --curPos.second;
}

void moveSW(std::pair<int, int> &curPos) {
    if (curPos.second % 2 == 0) {
        --curPos.first;
    }
    --curPos.second;
}

void followInst(const std::string &inst, std::set<std::pair<int, int> > &tiles) {
    std::pair<int, int> curPos = std::make_pair(0, 0);

    std::stringstream ss(inst);
    char c;
    while (ss >> c) {
        switch(c) {
            case 'e':
                moveE(curPos);
                break;
            case 'w':
                moveW(curPos);
                break;
            case 'n':
                ss >> c;
                if ( c == 'e') {
                    moveNE(curPos);
                } else if( c == 'w') {
                    moveNW(curPos);
                }
                break;
            case 's':
                ss >> c;
                if ( c == 'e') {
                    moveSE(curPos);
                } else if( c == 'w') {
                    moveSW(curPos);
                }
                break;    
        }
    }
    if (tiles.find(curPos) != tiles.end()) {
        tiles.erase(curPos);
    } else {
        tiles.insert(curPos);
    }
}

int flipTiles(const std::vector<std::string> &input) {
    std::set<std::pair<int, int> > tiles;

    for (auto const &inst : input) {
        followInst(inst, tiles);
    }

    return tiles.size();
}

int main() {
    std::vector<std::string> input;
    loadInput(input);

    int res = flipTiles(input);
    std::cout << "Number of black silde up tiles: " << res << std::endl;

    return 0;
}
