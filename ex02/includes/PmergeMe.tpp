#ifndef PMERGEME_TPP
#define PMERGEME_TPP

template<typename Iterator, typename T>
Iterator PmergeMe::my_lower_bound(Iterator first, Iterator last, const T& value, size_t& cmpCount)  {
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

#endif
