#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<int> &input) {
    std::ifstream file;
    file.open(INPUT);

    int cur;
    while (file >> cur) {
        input.push_back(cur);
    }

    file.close();
}

bool isValid(std::vector<int> &input) {
    for (int i = 1; i < input.size(); ++i) {
        if (input[i] - input[i - 1] > 3) {
            return false;
        }
    }
    return true;    
}

long getNumCombinations(std::vector<int> &input) {
    long *combinations = new long[input.size()] ();
    combinations[0] = 1;

    for (int i = 1; i < input.size(); ++i) {
        int j = i - 1;
        while (j >= 0 && input[j] >= input[i] - 3) {
            combinations[i] += combinations[j];
            --j;
        }
    }
    long res = combinations[input.size() - 1];
    delete[] combinations;
    return res;
}

int main() {
    std::vector<int> input;

    loadInput(input);
    // Add outlet and gizmo.
    std::sort(input.begin(), input.end());
    input.insert(input.begin(), 0);
    input.push_back(input[input.size() - 1] + 3);
    
    long combinations = getNumCombinations(input);
    std::cout << "Number of combinations: " << combinations << std::endl;

    return 0;
}
