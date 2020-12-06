#include <algorithm>
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

std::vector<int> getAllSeatId(const std::vector<std::string> &input) {
    std::vector<int> res;
    
    for (auto const& line : input) {
        int row = binarySearch(0, 127, line.substr(0, 7), 'F');
        int seat = binarySearch(0, 7, line.substr(7, 3), 'L');
        int seatId = row * 8 + seat;
        res.push_back(seatId);
    }

    return res;
}

int getYourSeatId(const std::vector<int> &seatId) {
    for (int i = 1; i < seatId.size(); ++i) {
        if (seatId[i - 1] + 2 == seatId[i]) {
            return seatId[i] - 1;
        }
     }

    return -1;
}

int main() {
    std::vector<std::string> input;

    loadInput(input);

    std::vector<int> seatId  = getAllSeatId(input);
    std::sort(seatId.begin(), seatId.end());
    int yourSeatId = getYourSeatId(seatId);

    std::cout << "Your seat id: " << yourSeatId << std::endl;

    return 0;
}
