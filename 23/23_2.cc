#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#define INPUT "input"
#define MILLION 1000000
#define TURNS 10000000

struct cup {
    int val;
    cup *next;
};

void loadInput(cup *cups[MILLION + 1], int &first) {
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
    // Fill up list and make circular.
    cup *curCup = cups[first];
    while (curCup->next != nullptr) {
        curCup = curCup->next;
    }
    int curVal = 10;
    while (curVal <= MILLION) {
        cup *newCup = new cup;
        cups[curVal] = newCup;
        newCup->val = curVal;
        curCup->next = newCup;
        curCup = curCup->next;
        ++curVal;
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
    int dest = cur->val > 1 ? cur->val - 1 : MILLION;

    while (contains(threeCups, dest)) {
        dest = dest > 1 ? dest - 1 : MILLION;
    }

    return dest;
}

void playGame(cup *cups[MILLION + 1], const int &first) {
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
}

int main() {
    cup *cups[MILLION + 1];
    int first = 0;
    loadInput(cups, first);
    
    playGame(cups, first);

    long res = (long)cups[1]->next->val * (long)cups[1]->next->next->val;
    std::cout << "Solution: " << res << std::endl;

    // Cleanup memory
    for (int i = 1; i < MILLION + 1; ++i) {
        delete cups[i];
    }

    return 0;
}
