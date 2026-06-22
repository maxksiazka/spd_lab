#include "LookThroughSolver.hpp"
#include <algorithm>

Solution LookThroughSolver::solve(const Problem& problem)
{
    const auto& tasks = problem.getTasks();
    const int n = tasks.size();
    const int m = problem.get_num_machines();

    Solution best_sol(n);
    Solution current_sol(n);
    int best_makespan = std::numeric_limits<int>::max();

    do {
        VectorI current_loads(m, 0);
        
        for (int i = 0; i < n; ++i) {
            current_loads[current_sol.sequence[tasks[i].idx]] += tasks[i].processing_time;
        }

        int current_makespan = *std::max_element(current_loads.begin(), current_loads.end());

        if (current_makespan < best_makespan) {
            best_makespan = current_makespan;
            best_sol = current_sol;
        }

    } while (current_sol.sequence.next_permutation(m));

    best_sol.evaluate(problem);

    return best_sol;
}