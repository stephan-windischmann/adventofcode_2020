#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define INPUT "input"
#define DAYS 100

struct tile {
    std::pair<int, int> coord;
    std::vector<std::pair<int, int> >  neighbors;
};

void loadInput(std::vector<std::string> &input) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    while (std::getline(file, line)) {
        input.push_back(line);
    }
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

void initTiles(const std::vector<std::string> &input, \
    std::set<std::pair<int, int> > &tiles) {
    

    for (auto const &inst : input) {
        followInst(inst, tiles);
    }
}

std::vector<std::pair<int, int> > getNeighbors(const std::pair<int, int> pos) {
    std::vector<std::pair<int, int> > res;

    // E
    res.push_back(std::make_pair(pos.first + 1, pos.second));
    // W
    res.push_back(std::make_pair(pos.first - 1, pos.second));
    // NE
    if (pos.second % 2 != 0) {
        res.push_back(std::make_pair(pos.first + 1, pos.second + 1));
    } else {
        res.push_back(std::make_pair(pos.first, pos.second + 1));
    }
    // NW
    if (pos.second % 2 == 0) {
        res.push_back(std::make_pair(pos.first - 1, pos.second + 1));
    } else {
        res.push_back(std::make_pair(pos.first, pos.second + 1));
    }
    // SE
    if (pos.second % 2 != 0) {
        res.push_back(std::make_pair(pos.first + 1, pos.second - 1));
    } else {
        res.push_back(std::make_pair(pos.first, pos.second - 1));
    }
    // SW
    if (pos.second % 2 == 0) {
        res.push_back(std::make_pair(pos.first - 1, pos.second - 1));
    } else {
        res.push_back(std::make_pair(pos.first, pos.second - 1));
    }

    return res;
}

void runFlip(std::set<std::pair<int, int> > &tiles, const int days) {
    for (int i = 0; i < days; ++i) {
        std::set<std::pair<int, int> > newTiles;
        std::set<std::pair<int, int> > whiteNeighbors;

        for (auto const &t : tiles) {
            auto neighbors = getNeighbors(t);
            int blackN = 0;
            for (auto const &p : neighbors) {
                if (tiles.find(p) == tiles.end()) {
                    whiteNeighbors.insert(p);
                } else {
                    ++blackN;
                }
            }
            if (blackN > 0 && blackN < 3) {
                newTiles.insert(t);
            }
        }
        for (auto const &t : whiteNeighbors) {
            auto neighbors = getNeighbors(t);
            int blackN = 0;
            for (auto const &p : neighbors) {
                if (tiles.find(p) != tiles.end()) {
                    ++blackN;
                }
            }
            if (blackN == 2) {
                newTiles.insert(t);
            }
        }
        tiles = newTiles;
    }
}

int main() {
    std::vector<std::string> input;
    loadInput(input);

    std::set<std::pair<int, int> > tiles;
    initTiles(input, tiles);
    runFlip(tiles, DAYS);

    std::cout << "Number of black silde up tiles: " << tiles.size() << std::endl;

    return 0;
}
