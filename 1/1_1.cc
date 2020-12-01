#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#define INPUT "input"

#define TARGET 2020

void loadInput(std::vector<int> &input) {
    std::ifstream file;
    file.open(INPUT);

    int num;

    while (file >> num) {
        input.push_back(num);
    }
}

int main() {
    // Input vector
    std::vector<int> input;
    // Work map
    std::map<int, int> data;
    

    // Load input into vector
    loadInput(input);

    for (int i = 0; i < input.size(); ++i) {
        data[input[i]] = i;
    }

    for (auto const& num : input) {
        int want = TARGET - num;

        auto search = data.find(want);
        if (search != data.end()) {
            std::cout << num << " + " << input[data[want]] << " = " \
                << TARGET << std::endl;
            std::cout << num << " * " << input[data[want]] << " = " \
                << num * input[data[want]] << std::endl;
            break;
        }
    }

    return 0;
}
