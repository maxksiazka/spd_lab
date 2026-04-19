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
    // populacja początkowej permutacji (kolejność zadań)
    int min_start_time = 0;
    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].rj > min_start_time) {
            min_start_time = tasks[i].rj; 
        }
        perm[i] = {i, min_start_time, tasks[i].pj}; 
    }
    // sortujemy zadania według rosnącego pożądanego czasu zakończenia (dj)
    std::sort(perm.begin(), perm.end(),
              [&tasks](const subtask& i, const subtask& j) { return tasks[i.idx].dj < tasks[j.idx].dj; });

    solution.evaluate(problem);
    return solution;
}
