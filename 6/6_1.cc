#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INPUT "input"

void loadInput(std::vector<std::string> &input) {
    std::fstream ifstream;

    ifstream.open(INPUT);

    std::string line;
    while (std::getline(ifstream, line)) {
        input.push_back(line);
    }

    ifstream.close();
}

int countQuestions(const std::vector<std::string> &input) {
    int res = 0;
    
    for (int i = 0; i < input.size(); ++i) {
        int q[26] {0};

        while (input[i] != "") {
            for (auto const& c : input[i]) {
                if (q[c - 'a'] == 0) {
                    q[c - 'a'] = 1;
                    ++res;
                }
            }
            ++i;
        }
    }

    return res;
}

int main() {
    std::vector<std::string> input;
    loadInput(input);
    
    int count = countQuestions(input);

    std::cout << "Sum of question count: " << count << std::endl;

    return 0;
}

