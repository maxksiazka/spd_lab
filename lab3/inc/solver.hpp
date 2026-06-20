#ifndef SOLVER_HPP_
#define SOLVER_HPP_
#include "problem.hpp"
#include "solution.hpp"
class Solver {
  public:
    virtual std::string name() const = 0; // returns the name of the algorithm
    virtual ~Solver() = default;
    virtual Solution solve(const Problem& problem) = 0;
};
#endif /* SOLVER_HPP_ */
