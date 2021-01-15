#include <fstream>
#include <iostream>
#include <string>

#define INPUT "input"

void loadInput(int &cardKey, int &doorKey) {
    std::fstream file;
    file.open(INPUT);

    std::string line;
    std::getline(file, line);
    cardKey = std::stoi(line);
    std::getline(file, line);
    doorKey = std::stoi(line);

    file.close();
}

int getLoopSize(int subjNum, int date, int goal) {
    long val = 1;
    int ls = 0;
    do
    {
        val *= subjNum;
        val %= date;
        ++ls;
    } while (val != goal);
    
    return ls;
}

long calcKey(int subjNum, int date, int ls) {
    long val = 1;
    for (int i = 0; i < ls; ++i) {
        val *= subjNum;
        val %= date;        
    }
    return val;
}

int getEncryptKey(const int cardKey, const int doorKey) {
    const int subjNum = 7;
    const int date = 20201227;

    int cardLoopSize = getLoopSize(subjNum, date, cardKey);
    int doorLoopSize = getLoopSize(subjNum, date, doorKey);
    
    long cardEncryptKey = calcKey(doorKey, date, cardLoopSize);
    //long doorEncryptKey = calcKey(cardKey, date, doorLoopSize);
    
    return cardEncryptKey;
}

int main() {
    int cardKey;
    int doorKey;
    loadInput(cardKey, doorKey);

    int encryptKey = getEncryptKey(cardKey, doorKey);
    std::cout << "Encryption key: " << encryptKey << std::endl;

    return 0;
}
