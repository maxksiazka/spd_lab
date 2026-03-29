#ifndef EDDSOLVER_HPP_
#define EDDSOLVER_HPP_

#include "solver.hpp"

class EDDSolver : public Solver {
  public:
    ~EDDSolver() override = default;
    std::string name() const override {
        return "EDD (Earliest Due Date)";
    }
    Solution solve(const Problem& problem) override;
};
#endif
