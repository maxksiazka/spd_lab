#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include "permutation.hpp"
#include "problem.hpp"
#include <limits>

struct Solution {
    Solution(int n) : sequence(n) {
    }
    Solution(std::vector<int> seq) : sequence(seq) {
    }
    Permutation sequence;
    int makespan = std::numeric_limits<int>::max();
    int32_t evaluate(const Problem& problem);
};
#endif /* SOLUTION_HPP_ */
