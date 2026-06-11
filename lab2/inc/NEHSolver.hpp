#ifndef NEH_SOLVER_HPP_
#define NEH_SOLVER_HPP_

#include "solver.hpp"

class NEHSolver : public Solver {
  public:
    std::string name() const override {
        return "NEH";
    }
    Solution solve(const Problem& problem) override;
    ~NEHSolver() override = default;
};

#endif // NEH_SOLVER_HPP_
