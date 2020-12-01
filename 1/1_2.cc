#include <algorithm>
#include <fstream>
#include <iostream>
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

    // Load input into vector
    loadInput(input);

    // Sort input
    std::sort(input.begin(), input.end());

    for(int i = 0; i < input.size() - 2; ++i) {
        int l = i + 1;
        int r = input.size() - 1;
        while (l < r) {
            int res = input[i] + input[l] + input[r];
            if (res == TARGET) {
                std::cout << input[i] << " + " << input[l] << " + " \
                    << input[r] << " = " << TARGET << std::endl;
                std::cout << input[i] << " * " << input[l] << " * " \
                    << input[r] << " = " << input[i] * input[l] * input[r] << std::endl;
                break;
            } else if (res < TARGET) {
                ++l;
            } else {
                --r;
            }
        }
    }

    return 0;
}
