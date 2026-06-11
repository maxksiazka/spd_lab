#ifndef LOOKTHROUGH_SOLVER_HPP_
#define LOOKTHROUGH_SOLVER_HPP_

#include "solver.hpp"

class LookthroughSolver : public Solver {
  public:
    std::string name() const override {
        return "LookThrough";
    }
    Solution solve(const Problem& problem) override;
    ~LookthroughSolver() override = default;
};

#endif // LOOKTHROUGH_SOLVER_HPP_
