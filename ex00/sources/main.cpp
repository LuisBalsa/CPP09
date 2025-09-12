#include "../includes/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    BitcoinExchange btc("data.csv"); // Assumes the database is named data.csv
    btc.processInputFile(argv[1]);
    return 0;
}
