#ifndef DYNAMIC_SOLVER_HPP_
#define DYNAMIC_SOLVER_HPP_
#include "solver.hpp"

class DynamicSolver : public Solver {
  public:
    std::string name() const override {
        return "Dynamic";
    }
    Solution solve(const Problem& problem) override;
    ~DynamicSolver() override = default;
};

#endif // DYNAMIC_SOLVER_HPP_
