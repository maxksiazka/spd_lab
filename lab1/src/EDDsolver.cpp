#include "EDDsolver.hpp"
#include <algorithm>
// Implementacja algorytmu EDD (Earliest Due Date)
// Potraktuj to jako templatkę do implementacji innych algorytmów.
// Wystarczy zmienić kryterium sortowania na inny algorytm np. Schrage
Solution EDDSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;
    // sortujemy zadania według rosnącego pożądanego czasu zakończenia (dj)
    std::sort(
        perm.begin(), perm.end(),
        [&tasks](int i, int j) { return tasks[i].dj < tasks[j].dj; });

    solution.evaluate(problem);
    return solution;
}
