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
    static Iterator my_lower_bound(Iterator first, Iterator last, const T& value, size_t& cmpCount);

    static size_t vectorComparisons;
    static size_t dequeComparisons;

};

#include "PmergeMe.tpp"

#endif
