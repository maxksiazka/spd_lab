#ifndef BranchAndBoundSOLVER_HPP_
#define BranchAndBoundSOLVER_HPP_

#include "solver.hpp"

typedef std::vector<int> VectorI;

class BranchAndBoundSolver : public Solver {
  public:
    std::string name() const override {
        return "BranchAndBound";
    }
    Solution solve(const Problem& problem) override;
    ~BranchAndBoundSolver() override = default;

  private:
    void LookThroughForN(
      int current_task, int n, int m,
      const std::vector<Task>& tasks, 
      VectorI& current_loads, 
      VectorI& current_assignment, 
      int& best_makespan,
      VectorI& best_assignment);
};

#endif /* BranchAndBoundSOLVER_HPP_ */
