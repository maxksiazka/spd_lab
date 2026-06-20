#ifndef LSASOLVER_HPP_
#define LSASOLVER_HPP_

#include "solver.hpp"

class LSASolver : public Solver {
  public:
    std::string name() const override {
        return "LSA";
    }
    Solution solve(const Problem& problem) override;
    ~LSASolver() override = default;
};

#endif /* LSASOLVER_HPP_ */
