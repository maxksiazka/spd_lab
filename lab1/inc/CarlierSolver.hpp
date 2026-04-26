#ifndef CARLIER_SOLVER_HPP_
#define CARLIER_SOLVER_HPP_

#include "solver.hpp"

class CarlierSolver : public Solver {
  public:
    ~CarlierSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif // CARLIER_SOLVER_HPP_
