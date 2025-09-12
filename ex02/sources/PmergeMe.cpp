
#include "../includes/PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// Generate Jacobsthal sequence up to n
static std::vector<int> generateJacobsthal(int n) 
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    while (jacobsthal[jacobsthal.size() - 1] < n) {
        int next = jacobsthal[jacobsthal.size()-1] + 2 * jacobsthal[jacobsthal.size()-2];
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

// Generate insertion order based on Jacobsthal sequence
static std::vector<int> generateInsertionOrder(int n) 
{
    std::vector<int> empty;
    if (n <= 1) 
        return empty;
    std::vector<int> jacobsthal = generateJacobsthal(n);
    std::vector<int> order;
    order.push_back(1);
    for (size_t i = 2; i < jacobsthal.size() && jacobsthal[i-1] < n; ++i) 
    {
        int groupStart = jacobsthal[i-1] + 1;
        int groupEnd = std::min(jacobsthal[i], n);
        for (int pos = groupEnd; pos >= groupStart; --pos) 
        {
            order.push_back(pos);
        }
    }
    return order;
}

// Ford-Johnson merge-insert sort for vector (PURE IMPLEMENTATION)
void PmergeMe::sortVector(std::vector<int>& v) 
{
    if (v.size() <= 1) 
        return;
    if (v.size() == 2) 
    {
        if (v[0] > v[1]) 
            std::swap(v[0], v[1]);
        return;
    }
    int straggler = -1;
    bool hasStraggler = false;
    if (v.size() % 2 != 0) 
    {
        straggler = v.back();
        v.pop_back();
        hasStraggler = true;
    }
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < v.size(); i += 2) 
    {
        int a = v[i], b = v[i+1];
        pairs.push_back(std::make_pair(a > b ? a : b, a > b ? b : a));
    }
    std::sort(pairs.begin(), pairs.end());
    std::vector<int> majors, minors;
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        majors.push_back(pairs[i].first);
        minors.push_back(pairs[i].second);
    }
    sortVector(majors);
    std::vector<int> mainChain;
    for (size_t i = 0; i < majors.size(); ++i)
        mainChain.push_back(majors[i]);
    if (!minors.empty()) 
    {
        std::vector<int> jacobOrder = generateInsertionOrder((int)minors.size());
        std::vector<bool> inserted(minors.size(), false);
        for (size_t k = 0; k < jacobOrder.size(); ++k) 
        {
            int idx = jacobOrder[k];
            if (idx < (int)minors.size() && !inserted[idx]) 
            {
                std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[idx]);
                mainChain.insert(pos, minors[idx]);
                inserted[idx] = true;
            }
        }
        for (size_t i = 0; i < minors.size(); ++i) 
        {
            if (!inserted[i]) 
            {
                std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[i]);
                mainChain.insert(pos, minors[i]);
            }
        }
    }
    if (hasStraggler) 
    {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    v = mainChain;
}

// Ford-Johnson merge-insert sort for deque (PURE IMPLEMENTATION)
void PmergeMe::sortDeque(std::deque<int>& d) {
    if (d.size() <= 1) return;
    if (d.size() == 2) {
        if (d[0] > d[1]) std::swap(d[0], d[1]);
        return;
    }
    int straggler = -1;
    bool hasStraggler = false;
    if (d.size() % 2 != 0) {
        straggler = d.back();
        d.pop_back();
        hasStraggler = true;
    }
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < d.size(); i += 2) {
        int a = d[i], b = d[i+1];
        pairs.push_back(std::make_pair(a > b ? a : b, a > b ? b : a));
    }
    std::sort(pairs.begin(), pairs.end());
    std::deque<int> majors;
    std::vector<int> minors;
    for (size_t i = 0; i < pairs.size(); ++i) {
        majors.push_back(pairs[i].first);
        minors.push_back(pairs[i].second);
    }
    sortDeque(majors);
    std::deque<int> mainChain;
    for (size_t i = 0; i < majors.size(); ++i)
        mainChain.push_back(majors[i]);
    if (!minors.empty()) {
        std::vector<int> jacobOrder = generateInsertionOrder((int)minors.size());
        std::vector<bool> inserted(minors.size(), false);
        for (size_t k = 0; k < jacobOrder.size(); ++k) {
            int idx = jacobOrder[k];
            if (idx < (int)minors.size() && !inserted[idx]) {
                std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[idx]);
                mainChain.insert(pos, minors[idx]);
                inserted[idx] = true;
            }
        }
        for (size_t i = 0; i < minors.size(); ++i) {
            if (!inserted[i]) {
                std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[i]);
                mainChain.insert(pos, minors[i]);
            }
        }
    }
    if (hasStraggler) {
        std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    d = mainChain;
}

