#include "LookthroughSolver.hpp"
#include <algorithm>
// Implementacja przeglądu zupełnego dla 1|rj|Lmax
// potraktuj to jako templatkę do implementacji innych algorytmów.
// wystarczy zmienić kryterium sortowania na inny algorytm np. schrage
std::string LookthroughSolver::name() const {
    return "Przegląd zupełny (LookthroughSolver)";
}
Solution LookthroughSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;
    // sortujemy zadania według rosnącego pożądanego czasu zakończenia (dj)

    int32_t min_lateness = std::numeric_limits<int32_t>::max();
    Permutation min_perm = perm;

    do {
        solution.max_lateness= std::numeric_limits<int32_t>::min();
        int32_t late = solution.evaluate(problem);
        //std::cout << "Sprawdzam permutację: " << perm << " Wynik: " << late << std::endl; 
        if (late < min_lateness) {
            min_lateness = late;
            min_perm = perm;
        }
    } while (perm.next_permutation());
    perm = min_perm;
    solution.max_lateness = min_lateness;
    return solution;
}
