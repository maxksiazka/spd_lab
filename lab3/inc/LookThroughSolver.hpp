#ifndef LOOKTHROUGHSOLVER_HPP_
#define LOOKTHROUGHSOLVER_HPP_

#include "solver.hpp"

typedef std::vector<int> VectorI;

class LookThroughSolver : public Solver {
  public:
    std::string name() const override {
        return "LookThrough";
    }
    Solution solve(const Problem& problem) override;
    ~LookThroughSolver() override = default;
};

#endif /* LookThroughSOLVER_HPP_ */
