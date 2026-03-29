#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include "permutation.hpp"
#include "problem.hpp"
#include <limits>

struct Solution {
    Solution(int n) : sequence(n) {
    }
    Permutation sequence; // sequence of job indices
    int max_lateness =
        std::numeric_limits<int>::min(); // maximum completion time (Lmax), inicjalizujemy na minimum
    void evaluate(const Problem& problem);
};
#endif /* SOLUTION_HPP_ */
