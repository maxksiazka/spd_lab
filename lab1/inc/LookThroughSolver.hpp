#ifndef LOOKTHROUGHSOLVER_HPP_
#define LOOKTHROUGHSOLVER_HPP_

#include "solver.hpp"

class LookThroughSolver : public Solver {
  public:
    ~LookThroughSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
