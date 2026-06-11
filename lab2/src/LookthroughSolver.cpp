#include "LookthroughSolver.hpp"

Solution LookthroughSolver::solve(const Problem& problem) {
    int n = problem.getTasks().size();

    Solution best_sol(n);
    Solution current_sol(n);

    do {
        int current_makespan = current_sol.evaluate(problem);

        if (current_makespan < best_sol.makespan) {
            best_sol = current_sol;
        }

    } while (current_sol.sequence.next_permutation());

    return best_sol;
}
