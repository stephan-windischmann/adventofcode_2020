#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <tuple>

#define INPUT "input"
#define MAX_TURN 6

class Cube {
    private:
        int x, y, z, w;
        std::set<std::tuple<int, int, int, int> > neighbors;

    public:
        Cube() {}
        Cube(int x, int y, int z, int w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;

            // Neighbors
            for (int x_ = x - 1; x_ < x + 2; ++x_) {
                for (int y_ = y - 1; y_ < y + 2; ++y_) {
                    for (int z_ = z - 1; z_ < z + 2; ++z_) {
                        for (int w_ = w - 1; w_ < w + 2; ++w_) {
                            if (! (x_ == x && y_ == y && z_ == z && w_ == w)) {
                            neighbors.insert(std::make_tuple(x_, y_, z_, w_));
                           }
                        }                     
                    }
                }
            }
        }

        std::set<std::tuple<int, int, int, int> > getNeighbors() {
            return neighbors;
        }
};

void loadInput(std::map<std::tuple<int, int, int, int>, Cube> &input) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    int y = 0;
    int z = 0;
    int w = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == '#') {
                Cube cur(x, y, z, w);
                input[std::make_tuple(x, y, z, w)] =  cur;
            }
        }
        ++y;
    }

    file.close();
}

int run (std::map<std::tuple<int, int, int, int>, Cube> &input) {
    for (int i = 0; i < MAX_TURN; ++i) {
        std::map<std::tuple<int, int, int, int>, Cube> newState;

        for (auto& cube : input) {
            auto neighbors = cube.second.getNeighbors();
            int nC = 0;
            for (auto& neighbor : neighbors) {
                if (input.find(neighbor) != input.end()) {
                    ++nC;
                }
                int x = std::get<0>(neighbor);
                int y = std::get<1>(neighbor);
                int z = std::get<2>(neighbor);
                int w = std::get<3>(neighbor);
                Cube cur(x, y, z, w);
                auto curNs = cur.getNeighbors();
                int curNC = 0;
                for (auto& curN : curNs) {
                    if (input.find(curN) != input.end()) {
                        ++curNC;
                    }
                }
                if (curNC == 3) {
                    newState[std::make_tuple(x, y, z, w)] = cur;
                }
            }
            if (nC >= 2 && nC <= 3) {
                newState[cube.first] = cube.second;
            }
        }

        input = newState;
    }
    return input.size();
}

int main() {

    std::map<std::tuple<int, int, int, int>, Cube> input;
    loadInput(input);
    
    int res = run(input);        
    std::cout << "Result: " << res << std::endl;

    return 0;
}

