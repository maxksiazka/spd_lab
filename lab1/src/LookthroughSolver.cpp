#include "LookthroughSolver.hpp"
// Implementacja przeglądu zupełnego dla 1|rj|Lmax
std::string LookthroughSolver::name() const {
    return "Przegląd zupełny (LookthroughSolver)";
}
Solution LookthroughSolver::solve(const Problem& problem) {
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

    int32_t min_lateness = std::numeric_limits<int32_t>::max();
    Permutation min_perm = perm;

    do {
        solution.max_lateness= std::numeric_limits<int32_t>::min();
        int32_t late = solution.evaluate(problem);
#ifndef NDEBUG
        std::cout << "Sprawdzam permutację: " << perm << " Wynik: " << late << std::endl; 
#endif
        if (late < min_lateness) {
            min_lateness = late;
            min_perm = perm;
        }
    } while (perm.next_permutation());
    perm = min_perm;
    solution.max_lateness = min_lateness;
    return solution;
}
