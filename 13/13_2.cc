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
        if (busId == "x") {
            bus.push_back(-1);
        } else {
            bus.push_back(std::stoi(busId));
        }
    }

    file.close();
}

long long getResult(const std::vector<int> &input) {
    long long res;
    bool found = false;
    long long ts = 1;
    
    while (!found) {
        long long increase = 1;
        found = true;    
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] != -1) {
                if ((ts + i) % input[i] != 0) {
                    found = false;
                    break;
                }
                increase *= input[i];
                res = ts;
            }
        }
        ts += increase;
    }
    return res;
}

int main() {
    int timestamp;
    std::vector<int> bus;

    loadInput(timestamp, bus);

    long long res = getResult(bus);
    std::cout << "Result: " << res << std::endl;

    return 0;
}

