#ifndef JOHNSON_FOR_2M_HPP_
#define JOHNSON_FOR_2M_HPP_

#include "solver.hpp"

class JohnsonFor2M : public Solver {
  public:
    std::string name() const override {
        return "JohnsonFor2M";
    }
    Solution solve(const Problem& problem) override;
    ~JohnsonFor2M() override = default;
};

#endif // JOHNSON_FOR_2M_HPP_
