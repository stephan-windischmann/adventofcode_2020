#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#define INPUT "input"
#define TURNS 100

struct cup {
    int val;
    cup *next;
};

void loadInput(cup *cups[10], int &first) {
    std::fstream file;
    file.open(INPUT);

    char c;
    int prev = 0;
    while (file >> c) {
        int curCupVal = c - '0';
        if (first == 0) {
            first = curCupVal;
        }
        cup *curCup = new cup;
        cups[curCupVal] = curCup;
        curCup->val = curCupVal;
        curCup->next = nullptr;
        if (prev != 0) {
            cups[prev]->next = curCup;
        }
        prev = curCupVal;
    }
    // Make list circular.
    cup *curCup = cups[first];
    while (curCup->next != nullptr) {
        curCup = curCup->next;
    }
    curCup->next = cups[first];

    file.close();
}

bool contains(cup *threeCups, int dest) {
    while (threeCups != nullptr) {
        if (threeCups->val == dest) {
            return true;
        }
        threeCups = threeCups->next;
    }
    return false;
}

int getDestVal(cup *cur, cup *threeCups) {
    int dest = cur->val > 1 ? cur->val - 1 : 9;

    while (contains(threeCups, dest)) {
        dest = dest > 1 ? dest - 1 : 9;
    }

    return dest;
}

std::string playGame(cup *cups[10], const int &first) {
    cup *cur = cups[first];

    for (int i = 0; i < TURNS; ++i) {
        cup *nextThree = cur->next;
        cur->next = nextThree->next->next->next;
        nextThree->next->next->next = nullptr;
        int dest = getDestVal(cur, nextThree);
        nextThree->next->next->next = cups[dest]->next;
        cups[dest]->next = nextThree;
        cur = cur->next;    
    }

    std::stringstream res;
    cur = cups[1]->next;
    while (cur->val != 1) {
        res << cur->val;
        cur = cur->next;
    }
    return res.str();
}

int main() {
    cup *cups[10];
    int first = 0;
    loadInput(cups, first);

    std::string res = playGame(cups, first);
    std::cout << "Result: " << res << std::endl;

    // Cleanup memory
    for (int i = 1; i < 10; ++i) {
        delete cups[i];
    }

    return 0;
}
