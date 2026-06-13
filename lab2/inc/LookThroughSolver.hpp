#ifndef LOOKTHROUGH_SOLVER_HPP_
#define LOOKTHROUGH_SOLVER_HPP_

#include "solver.hpp"

class LookThroughSolver : public Solver {
  public:
    std::string name() const override {
        return "LookThrough";
    }
    Solution solve(const Problem& problem) override;
    ~LookThroughSolver() override = default;
};

#endif // LOOKTHROUGH_SOLVER_HPP_
