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

int binarySearch(int l, int r, std::string s, char low) {
    int i = 0;
    int mid = l + (r - l) / 2;
    while (l < r && i < s.size()) {
        if (s[i] == low) {
            r = mid;
        } else {
            l = mid + 1;
        }
        mid = l + (r - l) / 2;
        ++i;
    }
    return mid;
}

int getMaxSeatId(const std::vector<std::string> &input) {
    int res = 0;
    
    for (auto const& line : input) {
        int row = binarySearch(0, 127, line.substr(0, 7), 'F');
        int seat = binarySearch(0, 7, line.substr(7, 3), 'L');
        int seatId = row * 8 + seat;
        res = seatId > res ? seatId : res;
    }

    return res;
}

int main() {
    std::vector<std::string> input;

    loadInput(input);

    int maxSeatId = getMaxSeatId(input);

    std::cout << "Max seat id: " << maxSeatId << std::endl;

    return 0;
}
