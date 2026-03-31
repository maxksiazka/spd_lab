#ifndef LOOKTHROUGHSOLVER_HPP_
#define LOOKTHROUGHSOLVER_HPP_

#include "solver.hpp"

class LookthroughSolver : public Solver {
  public:
    ~LookthroughSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
