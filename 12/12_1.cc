#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
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

void move(const int &heading, const int &val, int &x, int &y) {
    switch(heading) {
        case 0:
            y += val;
            break;
        case 90:
            x += val;
            break;
        case 180:
            y -= val;
            break;
        case 270:
            x -= val;
            break;
    }
}

int getDistance(const std::vector<std::string> &input) {
    int heading = 90;
    
    int x = 0, y = 0;
    for (auto const& line : input) {
        char action = line[0];
        int val = std::stoi(line.substr(1));

        switch(action) {
            case 'N':
                move(0, val, x, y);
                break;
            case 'S':
                move(180, val, x, y);
                break;
            case 'E':
                move(90, val, x, y);
                break;
            case 'W':
                move(270, val, x, y);
                break;
            case 'R':
                heading = (heading + val) % 360;
                break;
            case 'L':
                heading = (360 + (heading - val)) % 360;
                break;
            case 'F':
                move(heading, val, x, y);
                break;
        }

    }

    return std::abs(x) + std::abs(y);
}

int main() {
    std::vector<std::string> input;
    loadInput(input);

    int dist = getDistance(input);
    std::cout << "Distance travelled: " << dist << std::endl;

    return 0;
}

