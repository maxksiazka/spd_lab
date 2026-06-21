#ifndef FPTAS_SOLVER_HPP_
#define FPTAS_SOLVER_HPP_
#include "solver.hpp"

class FPTASSolver : public Solver {
  public:
    std::string name() const override {
        return "FPTAS";
    }
    Solution solve(const Problem& problem) override;
    ~FPTASSolver() override = default;
};

#endif // FPTAS_SOLVER_HPP_
