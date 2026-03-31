#ifndef ERDSOLVER_HPP_
#define ERDSOLVER_HPP_

#include "solver.hpp"

class ERDSolver : public Solver {
  public:
    ~ERDSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
