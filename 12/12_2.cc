#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h> // To get M_PI
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

void rotateWP(const int &rotation, std::pair<int, int> &wp) {
    int oldX = wp.first;
    int oldY = wp.second;

    // Rotate point around origin (WP is relative to origin, i.e. ferry ) 
    // using well known formula.
    float radians = (M_PI / 180) * rotation;

    wp.first = std::round(oldX * std::cos(radians) + oldY * std::sin(radians));
    wp.second = std::round((-1) * (oldX * std::sin(radians)) + oldY * std::cos(radians));
}

int getDistance(const std::vector<std::string> &input) {
    std::pair<int, int> pos_ship; // Absolute position of ferry.
    std:: pair<int, int> wp; // Relative position of WP.

    pos_ship.first = 0;
    pos_ship.second = 0;
    wp.first = 10;
    wp.second = 1;

    for (auto const& line : input) {
        char action = line[0];
        int val = std::stoi(line.substr(1));

        switch(action) {
            case 'N':
                wp.second += val;
                break;
            case 'S':
                wp.second -= val;
                break;
            case 'E':
                wp.first += val;
                break;
            case 'W':
                wp.first -= val;
                break;
            case 'R':
                rotateWP(val, wp);
                break;
            case 'L':
                rotateWP(360 - val, wp);
                break;
            case 'F':
                pos_ship.first += (val * wp.first);
                pos_ship.second += (val * wp.second);
                break;
        }
    }

    return std::abs(pos_ship.first) + std::abs(pos_ship.second);
}

int main() {
    std::vector<std::string> input;
    loadInput(input);

    int dist = getDistance(input);
    std::cout << "Distance travelled: " << dist << std::endl;

    return 0;
}

