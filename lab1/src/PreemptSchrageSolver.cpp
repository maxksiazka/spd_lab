#include "PreemptSchrageSolver.hpp"
#include <algorithm>
#include <functional>
#include <queue>
// Implementacja algorytmu Schrage z wywłaszczaniem.
// Potraktuj to jako templatkę do implementacji innych algorytmów.
// Wystarczy zmienić kryterium sortowania na inny algorytm np. Schrage
typedef std::priority_queue<int, std::vector<int>,
                            std::function<bool(int, int)>>
    TaskPriorityQueue;
std::string PreemptSchrageSolver::name() const {
    return "SchrageRelaxed";
}
Solution PreemptSchrageSolver::solve(const Problem& problem) {
    std::vector<Task> tasks = problem.getTasks();
    Solution solution(0);
    Permutation& perm = solution.sequence;

    // zbiór zadań niegotowych U (Unready)
    std::vector<int> U(tasks.size());
    for (size_t i = 0; i < tasks.size(); ++i) {
        U[i] = i;
    }
    // sortowanie po rj malejaco - "stos"
    std::stable_sort(U.begin(), U.end(), [&tasks](int i, int j) {
        return tasks[i].rj > tasks[j].rj;
    });

    auto compareD = [&tasks](int i, int j) {
        return tasks[i].dj > tasks[j].dj;
    };

    TaskPriorityQueue G(compareD);

    int t = 0;

    while ((!U.empty() && G.empty()) || !G.empty()) {
        // dodajemy do G wszystkie zadania, które są gotowe do wykonania
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
#ifndef NDEBUG
        std::cout << "Current time: " << t
                  << ", executing task: " << current_task
                  << " (rj: " << tasks[current_task].rj
                  << ", pj: " << tasks[current_task].pj
                  << ", dj: " << tasks[current_task].dj << ")" << std::endl;
#endif

        int next_task = U.empty() ? std::numeric_limits<int>::max() : U.back();
        if (!U.empty() && t + tasks[current_task].pj > tasks[next_task].rj) {
            int start_time = t;
            t = tasks[next_task].rj;
#ifndef NDEBUG
            std::cout << "Adding task " << next_task << " at time " << t
                      << std::endl;
#endif
            tasks[current_task].pj -= t - start_time;
            perm.push_back({current_task, start_time, t - start_time});

            G.push(current_task);
        } else {
            perm.push_back({current_task, t, tasks[current_task].pj});
            t += tasks[current_task].pj;
#ifndef NDEBUG
            std::cout << "Finished task " << current_task << " at time " << t
                      << std::endl;
#endif
        }
    }

    solution.evaluate(problem);
    return solution;
}
