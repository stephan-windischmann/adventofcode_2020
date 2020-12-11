#include <fstream>
#include <iostream>
#include <vector>

#define INPUT "input"

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

int getNumOccupiedNeighbors(int x, int y, std::vector<std::vector<char> > &input) {
    int num = 0;

    if (x > 0 && y > 0 && input[y - 1][x - 1] == '#') {
        ++num;
    }
    if (y > 0 && input[y - 1][x] == '#') {
        ++num;
    }
    if (y > 0 && x < input[y].size() - 1 && input[y - 1][x + 1] == '#')  {
        ++num;
    }
    if (x < input[y].size() - 1 && input[y][x + 1] == '#') {
        ++num;
    }
    if (y < input.size() - 1 && x < input[y].size() && input[y + 1][x + 1] == '#') {
        ++num;
    }
    if (y < input.size() - 1 && input[y + 1][x] == '#') {
        ++num;
    }
    if (y < input.size() - 1 && x > 0 && input[y + 1][x - 1] == '#') {
        ++num;
    }
    if (x > 0 && input[y][x - 1] == '#') {
        ++num;
    }


    return num;
}

int getOccupiedSeats(std::vector<std::vector<char> > &input) {
    int res = 0;
    
    int changes;
    do {
        changes = 0;
        int numOccupied = 0;
    
        int **occupied = new int*[input.size()];
        for (int i = 0; i < input.size(); ++i) {
            occupied[i] = new int[input[i].size()] ();
        }
        
        for (int y = 0; y < input.size(); ++y) {
            for (int x = 0; x < input[y].size(); ++x) {
                if (input[y][x] == '.') {
                    continue;
                }

                int occupiedN = getNumOccupiedNeighbors(x, y, input);
                if (input[y][x] == '#') {
                    if (occupiedN < 4)     {
                        occupied[y][x] = 1;
                        ++numOccupied;
                    } else {
                        occupied[y][x] = 0;
                        ++changes;
                    }
                } else {
                    if (occupiedN == 0) {
                        occupied[y][x] = 1;
                        ++numOccupied;
                        ++changes;
                    } else {
                        occupied[y][x] = 0;
                    }
                }
            }
        }

        for (int y = 0; y < input.size(); ++y) {
            for (int x = 0; x < input[y].size(); ++x) {
                if (input[y][x] == '.') {
                    continue;
                }
                if (occupied[y][x] == 1) {
                    input[y][x] = '#';
                } else {
                    input[y][x] = 'L';
                }
            }
        }

        
        for (int i = 0; i < input.size(); ++i) {
            delete[] occupied[i];
        }
        delete[] occupied;

        res = numOccupied;
    } while (changes > 0);

    return res;
}

int main() {
    std::vector<std::vector<char> > input;
    loadInput(input);

    int res = getOccupiedSeats(input);
    std::cout << "Occupied seats: " <<  res << std::endl;

    return 0;
}

