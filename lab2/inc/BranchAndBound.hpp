#ifndef BRANCH_AND_BOUND_HPP_
#define BRANCH_AND_BOUND_HPP_

#include "solver.hpp"

class BranchAndBound : public Solver {
  public:
    std::string name() const override {
        return "BranchAndBound";
    }
    Solution solve(const Problem& problem) override;
    ~BranchAndBound() override = default;

  private:
    int calculate_lower_bound(const std::vector<int>& current_end_times, const std::vector<int>& remaining_tasks, const Problem& problem);
    void solve_bb(
    std::vector<int>& current_pi,
    std::vector<int>& remaining_tasks,
    std::vector<int>& current_end_times,
    int& best_cmax,
    std::vector<int>& best_pi,
    const Problem& problem);

    void solve_bb_fast(
    std::vector<int>& current_pi,
    std::vector<int>& remaining_tasks,
    const std::vector<int>& current_end_times,
    int& best_cmax,
    std::vector<int>& best_pi,
    std::vector<int>& sum_remaining,
    const std::vector<std::vector<int>>& tails,
    const std::vector<Task>& safe_tasks,
    int m
    );
};

#endif // BRANCH_AND_BOUND_HPP_
