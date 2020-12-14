#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#define INPUT "input"

enum Type { EMPTY, SEAT };

struct seat {
    Type type;
    bool occupied;
    std::vector<std::pair<int, int> > neighbors;
};

void loadInput(std::vector<std::vector<char> > &input) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string row;
    while (std::getline(file, row)) {
        std::vector<char> vec(row.begin(), row.end());
        input.push_back(vec);
    }

    file.close();
}

int getNumOccupiedNeighbors(int x, int y, std::vector<std::vector<char> > &input, \
        std::vector<std::vector<seat> > &seats) {
    int num = 0;

    for (auto const& nb : seats[y][x].neighbors) {
        if (input[nb.second][nb.first] == '#') {
            ++num;
        }
    }
    return num;
}

int getOccupiedSeats(std::vector<std::vector<char> > &input, \
        std::vector<std::vector<seat> > &seats) {
    int res = 0;
    
    int changes;
    do {
        changes = 0;
        int numOccupied = 0;

        for (int y = 0; y < input.size(); ++y) {
            for (int x = 0; x < input[y].size(); ++x) {
                if (input[y][x] == '.') {
                    continue;
                }

                int occupiedN = getNumOccupiedNeighbors(x, y, input, seats);
                if (input[y][x] == '#') {
                    if (occupiedN < 5)     {
                        seats[y][x].occupied = true;
                        ++numOccupied;
                    } else {
                        seats[y][x].occupied = false;
                        ++changes;
                    }
                } else {
                    if (occupiedN == 0) {
                        seats[y][x].occupied = true;
                        ++numOccupied;
                        ++changes;
                    } else {
                        seats[y][x].occupied = false;
                    }
                }
            }
        }

        for (int y = 0; y < input.size(); ++y) {
            for (int x = 0; x < input[y].size(); ++x) {
                if (input[y][x] == '.') {
                    continue;
                }
                if (seats[y][x].occupied) {
                    input[y][x] = '#';
                } else {
                    input[y][x] = 'L';
                }
            }
        }

        res = numOccupied;
    } while (changes > 0);

    return res;
}

std::vector<std::pair<int, int> > fillNeighbors(int x, int y, \
        std::vector<std::vector<char> > &input) {
    // Go from current point in all directions until we find the first visible seat.
    
    std::vector<std::pair<int, int> > res;

    std::vector<std::pair<int, int> > dirs {
        std::pair<int, int> {-1, 0},
        std::pair<int, int> {-1, -1},
        std::pair<int, int> {0, -1},
        std::pair<int, int> {+1, -1},
        std::pair<int, int> {+1, 0},
        std::pair<int, int> {+1, +1},
        std::pair<int, int> {0, +1},
        std::pair<int, int> {-1, +1}
    };    

    for (auto const& dir : dirs) {
        int stepX = dir.first;
        int stepY = dir.second;

        int curX = x + stepX;
        int curY = y + stepY;

        while(curX >= 0 && curY >= 0 && curY < input.size() && curX < input[y].size()) {
            if (input[curY][curX] == 'L') {
                res.push_back(std::pair<int, int> {curX, curY});
                break;
            }
            curX += stepX;
            curY += stepY;
        }
    }

    return res;
}

void fillSeats(std::vector<std::vector<char> > &input, \
        std::vector<std::vector<seat> > &seats) {
    for (int y = 0; y < input.size(); ++y) {
        std::vector<seat> row;
        for (int x = 0; x < input[y].size(); ++x) {
            seat curSeat;
            if (input[y][x] == '.') {
                curSeat.type = EMPTY;
            } else {
                curSeat.type = SEAT;
                curSeat.occupied = false;
                curSeat.neighbors = fillNeighbors(x, y, input);
            }
            row.push_back(curSeat);
        }
        seats.push_back(row);
    }
}

int main() {
    std::vector<std::vector<char> > input;
    std::vector<std::vector<seat> > seats;

    loadInput(input);
    fillSeats(input, seats);
   
    int res = getOccupiedSeats(input, seats);
    std::cout << "Occupied seats: " <<  res << std::endl;

    return 0;
}

