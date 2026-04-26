#ifndef CONSTRUCTION_SOLVER_HPP_
#define CONSTRUCTION_SOLVER_HPP_

#include "solver.hpp"

class ConstructionSolver : public Solver {
  public:
    ~ConstructionSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
