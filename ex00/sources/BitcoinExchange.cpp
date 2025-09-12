#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

// Constructor: loads the database from the CSV file
BitcoinExchange::BitcoinExchange(const std::string& dbFile) {
    loadDatabase(dbFile);
}

// Destructor
BitcoinExchange::~BitcoinExchange() {}

// Loads the database into the map
void BitcoinExchange::loadDatabase(const std::string& dbFile) {
    std::ifstream file(dbFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }
    std::string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string date, valueStr;
        if (getline(iss, date, ',') && getline(iss, valueStr)) {
            float value = static_cast<float>(atof(valueStr.c_str()));
            _db[date] = value;
        }
    }
    file.close();
}

// Checks if the date is valid (format: YYYY-MM-DD and real calendar date)
bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    // Check if all other characters are digits
    for (size_t i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    // Parse year, month, day
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;
    int maxDay = 31;
    switch (month) {
        case 2:
            {
                bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
                maxDay = isLeap ? 29 : 28;
            }
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
    }
    if (day > maxDay)
        return false;
    return true;
}

// Checks if the value is a valid float or positive integer between 0 and 1000
bool BitcoinExchange::isValidValue(const std::string& value) const {
    char* end;
    double val = strtod(value.c_str(), &end);
    if (*end != '\0')
        return false;
    if (val < 0.0 || val > 1000.0)
        return false;
    return true;
}

// Gets the closest lower or equal date's rate
float BitcoinExchange::getClosestRate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it = _db.lower_bound(date);
    if (it == _db.end() || it->first != date) {
        if (it == _db.begin())
            return 0.0f;
        --it;
    }
    return it->second;
}

// Processes the input file, validates, and outputs results
void BitcoinExchange::processInputFile(const std::string& inputFile) const {
    std::ifstream input(inputFile.c_str());
    if (!input.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    getline(input, line); // skip header
    while (getline(input, line)) {
        std::istringstream iss(line);
        std::string date, valueStr;
        
        size_t pipe = line.find('|');
        if (pipe == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = line.substr(0, pipe);
        valueStr = line.substr(pipe + 1);
        // Trim whitespace
        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        float value = static_cast<float>(atof(valueStr.c_str()));
        if (!isValidValue(valueStr)) {
            if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else if (value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else
                std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        float rate = getClosestRate(date);
        float result = value * rate;
        std::cout << date << " => " << valueStr << " = " << result << std::endl;
    }
}