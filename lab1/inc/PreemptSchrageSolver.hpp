#ifndef PREEMPTSCHRAGESOLVER_HPP_
#define PREEMPTSCHRAGESOLVER_HPP_

#include "solver.hpp"

class PreemptSchrageSolver : public Solver {
  public:
    ~PreemptSchrageSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif
