#ifndef SCHRAGESOLVER_HPP_
#define SCHRAGESOLVER_HPP_

#include "solver.hpp"

class SchrageSolver : public Solver {
  public:
    ~SchrageSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
