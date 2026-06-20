#ifndef FNEH_SOLVER_HPP_
#define FNEH_SOLVER_HPP_

#include "solver.hpp"

class FNEHSolver : public Solver {
  public:
    std::string name() const override {
        return "FNEH";
    }
    Solution solve(const Problem& problem) override;
    ~FNEHSolver() override = default;
};

#endif // FNEH_SOLVER_HPP_
