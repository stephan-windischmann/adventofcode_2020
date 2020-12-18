#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "INPUT"

class TicketField {
    private:
        int low1;
        int low2;
        int high1;
        int high2;
        std::string name;

    public:
        TicketField(int low1, int high1, int low2, int high2, std::string name) {
            this->low1 = low1;
            this->low2 = low2;
            this->high1 = high1;
            this->high2 = high2;
            this->name = name;
        }

        bool isValid(int num) {
            if ((num >= low1 && num <= high1) || (num >= low2 && num <= high2)) {
                return true;
            }
            return false;
        }
};

void loadInput(std::vector<TicketField> &fields, std::vector<int> &myTicket,\
        std::vector<std::vector<int > > &otherTickets) {
    std::ifstream file;
    file.open(INPUT);
    
    std::string line;
    while (std::getline(file, line)) {
        if (line == "") {
            continue;
        }
        if (line == "your ticket:") {
            break;
        }
        std::regex e("(.+):\\s(\\d+)-(\\d+)\\sor\\s(\\d+)-(\\d+)");
        std::smatch sm;
        std::regex_match(line.cbegin(), line.cend(), sm, e);
        std::string name = sm[1];
        int low1 = std::stoi(sm[2]);
        int high1 = std::stoi(sm[3]);
        int low2 = std::stoi(sm[4]);
        int high2 = std::stoi(sm[5]);

        fields.push_back(TicketField(low1, high1, low2, high2, name));
    }
    std::getline(file, line);
    std::stringstream ss(line);
    std::string num;
    while (std::getline(ss, num, ',')) {
        myTicket.push_back(std::stoi(num));
    }

    std::getline(file, line);
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> curTicket;
        while (std::getline(ss, num, ',')) {
            curTicket.push_back(std::stoi(num));
        }
        otherTickets.push_back(curTicket);
    }

    file.close();
}

bool isValidField(int num, std::vector<TicketField> &fields) {
    bool foundValid = false;

    for (auto &field : fields) {
        if (field.isValid(num)) {
            foundValid = true;
            break;
        }
    }

    return foundValid;
}

int scanOtherTickets(std::vector<TicketField> &fields, \
        const std::vector<std::vector<int> > &otherTickets) {
    int res = 0;

    for (auto const& ticket : otherTickets) {
        for (auto const& num : ticket)  {
            if (!isValidField(num, fields)) {
                res += num;
            }
        }
    }

    return res;
}

int main() {
    std::vector<TicketField> fields;
    std::vector<int> myTicket;
    std::vector<std::vector<int> > otherTickets;

    loadInput(fields, myTicket, otherTickets);
    
    int errRate = scanOtherTickets(fields, otherTickets);
    std::cout << "Ticket error rate: " << errRate << std::endl;

    return 0;
}

