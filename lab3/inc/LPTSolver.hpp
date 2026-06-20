#ifndef LPTSOLVER_HPP_
#define LPTSOLVER_HPP_

#include "solver.hpp"

class LPTSolver : public Solver {
  public:
    std::string name() const override {
        return "LPT";
    }
    Solution solve(const Problem& problem) override;
    ~LPTSolver() override = default;
};

#endif /* LPTSOLVER_HPP_ */
