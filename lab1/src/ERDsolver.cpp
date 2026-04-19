#include "ERDsolver.hpp"
#include <algorithm>
// implementacja algorytmu edd (earliest due date)
// potraktuj to jako templatkę do implementacji innych algorytmów.
// wystarczy zmienić kryterium sortowania na inny algorytm np. schrage
std::string ERDSolver::name() const {
    return "erd (earliest release date)";
}
Solution ERDSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;
    // populacja początkowej permutacji (kolejność zadań)
    for (int i = 0; i < tasks.size(); ++i) {
        perm[i] = {i, tasks[i].rj, tasks[i].pj}; 
    }
    std::stable_sort(perm.begin(), perm.end(),
            [&tasks](const subtask& i, const subtask& j) { return tasks[i.idx].rj < tasks[j.idx].rj; });

    solution.evaluate(problem);
    return solution;
}
