#include "../includes/PmergeMe.hpp"
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdlib>

template <typename Container>
void printContainer(const Container& c) {
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::vector<int> v;
    std::deque<int> d;
    for (int i = 1; i < argc; ++i) {
        char* end;
        long n = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || n <= 0 || n > 2147483647) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        v.push_back(static_cast<int>(n));
        d.push_back(static_cast<int>(n));
    }
    std::cout << "Before: ";
    printContainer(v);
    clock_t startVec = clock();
    PmergeMe::sortVector(v);
    clock_t endVec = clock();
    clock_t startDeq = clock();
    PmergeMe::sortDeque(d);
    clock_t endDeq = clock();
    std::cout << "After:  ";
    printContainer(v);
    double elapsedVec = 1.0 * (endVec - startVec) / CLOCKS_PER_SEC * 1e6;
    double elapsedDeq = 1.0 * (endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process a range of " << v.size() << " elements with std::vector : " << elapsedVec << " us" << std::endl;
    std::cout << "Time to process a range of " << d.size() << " elements with std::deque  : " << elapsedDeq << " us" << std::endl;
    return 0;
}
