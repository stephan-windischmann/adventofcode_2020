#include <algorithm>
#include <fstream>
#include <iostream>
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

int findResult(std::vector<int> &input) {
    int count_diff_1 = 0, count_diff_3 = 0;

    for (int i = 1; i < input.size(); ++i) {
        if (input[i - 1] + 1 == input[i]) {
            ++count_diff_1;
        }
        else if (input[i - 1] + 3 == input[i]) {
            ++count_diff_3;
        }
    }
    
    return count_diff_1 * count_diff_3;
}

int main() {
    std::vector<int> input;

    loadInput(input);
    // Add outlet and gizmo.
    std::sort(input.begin(), input.end());
    input.insert(input.begin(), 0);
    input.push_back(input[input.size() - 1] + 3);

    int res = findResult(input);

    std::cout << "Result: " << res << std::endl;

    return 0;
}
