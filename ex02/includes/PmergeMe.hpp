#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>

class PmergeMe {

public:
    static void sortVector(std::vector<int>& v);
    static void sortDeque(std::deque<int>& d);
    static void printComparisonCounts();

    // Custom lower_bound with comparison counting
    template<typename Iterator, typename T>
    static Iterator my_lower_bound(Iterator first, Iterator last, const T& value, size_t& cmpCount) {
        Iterator it;
        size_t count = std::distance(first, last);
        while (count > 0) {
            it = first;
            size_t step = count / 2;
            std::advance(it, step);
            ++cmpCount;
            if (*it < value) {
                first = ++it;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return first;
    }

    static size_t vectorComparisons;
    static size_t dequeComparisons;

};

#endif // PMERGEME_HPP
