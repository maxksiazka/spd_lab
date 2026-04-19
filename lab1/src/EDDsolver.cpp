#include "EDDsolver.hpp"
#include <algorithm>
// Implementacja algorytmu EDD (Earliest Due Date)
// Potraktuj to jako templatkę do implementacji innych algorytmów.
// Wystarczy zmienić kryterium sortowania na inny algorytm np. Schrage
std::string EDDSolver::name() const {
    return "EDD (Earliest Due Date)";
}
Solution EDDSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;
    for (int i = 0; i < tasks.size(); ++i) {
        perm[i] = {i, tasks[i].rj, tasks[i].pj}; 
    }
    // sortujemy zadania według rosnącego pożądanego czasu zakończenia (dj)
    std::sort(perm.begin(), perm.end(),
              [&tasks](const subtask& i, const subtask& j) { return tasks[i.idx].dj < tasks[j.idx].dj; });

    solution.evaluate(problem);
    return solution;
}
