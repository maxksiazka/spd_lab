#ifndef CARLIER_SOLVER_HPP_
#define CARLIER_SOLVER_HPP_

#include "solver.hpp"

class CarlierSolver : public Solver {
    int32_t best_Lmax = std::numeric_limits<int32_t>::max();
    Solution best_solution = Solution(0);
    int32_t find_b(const std::vector<Task>& tasks);
    int32_t find_a(const std::vector<Task>& tasks, int32_t b);
    int32_t find_c(const std::vector<Task>& tasks, int32_t a, int32_t b);
    void modify_tasks(std::vector<Task>& tasks, const Permutation& new_tasks);
    void carlier_recursive(std::vector<Task>& tasks);

  public:
    ~CarlierSolver() override = default;
    std::string name() const override;
    Solution solve(const Problem& problem) override;
};
#endif // CARLIER_SOLVER_HPP_
