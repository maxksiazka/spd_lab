#include "SchrageSolver.hpp"
#include <algorithm>
#include <queue>
// Implementacja algorytmu Schrage bez wywłaszczania (Non-preemptive)
// Potraktuj to jako templatkę do implementacji innych algorytmów.
// Wystarczy zmienić kryterium sortowania na inny algorytm np. Schrage
std::string SchrageSolver::name() const {
    return "Schrage";
}
Solution SchrageSolver::solve(const Problem& problem) {
    const std::vector<Task>& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;

    // zbiór zadań niegotowych U (Unready)
    std::vector<int> U(tasks.size());
    for (size_t i = 0; i < tasks.size(); ++i) {
        U[i] = i;
    }
    // sortowanie po rj malejaco - "stos"
    std::sort(U.begin(), U.end(),
              [&tasks](int i, int j) { return tasks[i].rj > tasks[j].rj; });

    auto compareD = [&tasks](int i, int j) {
        return tasks[i].dj > tasks[j].dj;
    };
    std::priority_queue<int, std::vector<int>, decltype(compareD)> G(compareD);

    int t = 0;
    int idx = 0;

    while (!U.empty() || !G.empty()) {

        while (!U.empty() && tasks[U.back()].rj <= t) {
            G.push(U.back());
            U.pop_back();
        }

        if (G.empty()) {
            t = tasks[U.back()].rj;
            continue;
        }

        int current_task = G.top();
        G.pop();

        perm[idx] = {current_task, t,
                     tasks[current_task].pj};
        idx++;

        t += tasks[current_task].pj;
    }

    solution.evaluate(problem);
    return solution;
}
