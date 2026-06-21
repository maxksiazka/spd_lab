#ifndef PTASSOLVER_HPP_
#define PTASSOLVER_HPP_

#include "solver.hpp"

typedef std::vector<int> VectorI;

class PTASSolver : public Solver {
  public:
    std::string name() const override {
        return "PTAS";
    }
    Solution solve(const Problem& problem) override;
    ~PTASSolver() override = default;

  private:
    void LookThroughForK(
                    int current_task, int k, int m, 
                    const std::vector<Task>& tasks, 
                    VectorI& current_loads, 
                    VectorI& current_assignment, 
                    int& best_makespan,
                    VectorI& best_assignment
    );

};

#endif /* PTASSOLVER_HPP_ */
