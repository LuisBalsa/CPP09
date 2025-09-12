#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {

public:

    BitcoinExchange(const std::string& dbFile);
    ~BitcoinExchange();

    // Encapsulates the input file processing and output
    void processInputFile(const std::string& inputFile) const;

    // Utility methods
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value) const;
    float getClosestRate(const std::string& date) const;
    void loadDatabase(const std::string& dbFile);
    
private:

    std::map<std::string, float> _db;

};

#endif
