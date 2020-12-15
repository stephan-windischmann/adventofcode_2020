#include <fstream>
#include <iostream>
#include <vector>

#define INPUT "input"

void loadInput(int &timestamp, std::vector<int> &bus) {
    std::ifstream file;
    file.open(INPUT);

    file >> timestamp;

    std::string busId;
    while (std::getline(file, busId, ',')) {
        if (busId != "x") {
            bus.push_back(std::stoi(busId));
        }
    }

    file.close();
}

int getResult(const int &timestamp, const std::vector<int> &input) {
    int minWait = input[0] - timestamp % input[0];
    int minBusId = input[0];

    for (int i = 1; i < input.size() ; ++i) {
        int curWait = input[i] - timestamp % input[i];
        if (curWait < minWait) {
            minWait = curWait;
            minBusId = input[i];
        }
    }

    return minBusId * minWait;
}

int main() {
    int timestamp;
    std::vector<int> bus;

    loadInput(timestamp, bus);

    int res = getResult(timestamp, bus);
    std::cout << "Result: " << res << std::endl;

    return 0;
}

