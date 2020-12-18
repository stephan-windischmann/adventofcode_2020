#include <fstream>
#include <iostream>
#include <regex>
#include <set>
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

        std::string getName() {
            return this->name;
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

void removeInvalidTickets(std::vector<TicketField> &fields, \
        std::vector<std::vector<int> > &otherTickets) {
    for (auto it = otherTickets.begin(); it != otherTickets.end();) {
        bool isValid = true;
        for (auto const& num : *it)  {
            if (!isValidField(num, fields)) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            ++it;
        } else {
            it = otherTickets.erase(it);
        }
    }
}

bool isFieldValid(TicketField &field, const std::vector<std::vector<int > > &otherTickets, int col) {
    for (auto const& ticket: otherTickets) {
        if (!field.isValid(ticket[col])) {
           return false; 
        }
    }

    return true;
}

void getPossibleFields(std::vector<TicketField> &fields, \
        std::vector<std::vector<int> > &otherTickets, \
        std::vector<std::set<int> > &possibleFields) {
    for (int i = 0; i < otherTickets[0].size(); ++i) {
        std::set<int> p;
        
        for (int j = 0; j < fields.size(); ++j) {
            if(isFieldValid(fields[j], otherTickets, i)) {
                p.insert(j);
            }
        }

        possibleFields.push_back(p);
    }
}

void cleanFields(std::vector<std::set<int> > &possibleFields) {
    bool changes = false;
    std::set<int> used;
    do {
        changes = false;
        for (auto& fields : possibleFields) {
            if (fields.size() == 1) {
                if (used.find(*fields.begin()) == used.end()) {
                    used.insert(*fields.begin());
                }
            } else {
                for (auto& i : used) {
                    if (fields.find(i) != fields.end()) {
                        fields.erase(i);
                        changes = true;
                    }
                }
            }
        }
    } while(changes);
}

long getRes(const std::vector<std::set<int> > possibleFields, \
        std::vector<int> myTicket, \
        std::vector<TicketField> fields) {
    long res = 1;
    
    for (int i = 0; i < myTicket.size(); ++i) {
        if (fields[*possibleFields[i].begin()].getName().substr(0, 9) == "departure") {
            res *= myTicket[i];
        }
    }

    return res;
}

int main() {
    std::vector<TicketField> fields;
    std::vector<int> myTicket;
    std::vector<std::vector<int> > otherTickets;

    loadInput(fields, myTicket, otherTickets);
    
    // First remove all invalid tickets.
    removeInvalidTickets(fields, otherTickets);

    // First loop, check which fields could be valid for a column.
    std::vector<std::set<int> > possibleFields;
    getPossibleFields(fields, otherTickets, possibleFields);

    // Now continiously loop through until only one field remains per column.
    cleanFields(possibleFields);

    long res = getRes(possibleFields, myTicket, fields);
    std::cout << "Result: " << res << std::endl;

    return 0;
}

