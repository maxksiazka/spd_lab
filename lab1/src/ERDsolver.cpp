#include "ERDsolver.hpp"
#include <algorithm>
// implementacja algorytmu edd (earliest due date)
// potraktuj to jako templatkę do implementacji innych algorytmów.
// wystarczy zmienić kryterium sortowania na inny algorytm np. schrage
std::string ERDSolver::name() const {
    return "edd (earliest due date)";
}
Solution ERDSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;
    // sortujemy zadania według rosnącego pożądanego czasu zakończenia (dj)
    std::sort(perm.begin(), perm.end(),
              [&tasks](int i, int j) { return tasks[i].dj < tasks[j].dj; });

    solution.evaluate(problem);
    return solution;
}
