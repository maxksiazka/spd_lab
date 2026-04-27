#include "CarlierSolver.hpp"
#include "PreemptSchrageSolver.hpp"
#include "SchrageSolver.hpp"
#include <algorithm>

std::string CarlierSolver::name() const {
    return "Carlier";
}
int32_t CarlierSolver::find_b(const std::vector<Task>& tasks) {
    int32_t current_time = 0;
    int32_t max_lateness = std::numeric_limits<int32_t>::min();
    int32_t b = -1;

    for (std::size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        current_time = std::max(current_time, task.rj) + task.pj;
        int32_t lateness = current_time - task.dj;

        if (lateness >= max_lateness) {
            max_lateness = lateness;
            b = i; // aktualizuj indeks zadania b
        }
    }
    return b;
}
int32_t CarlierSolver::find_a(const std::vector<Task>& tasks, int32_t b) {
    int32_t current_time = 0;
    int32_t completion_b = 0;
    for (int32_t i = 0; i <= b; ++i) {
        current_time = std::max(current_time, tasks[i].rj) + tasks[i].pj;
        if (i == b)
            completion_b = current_time;
    }
    for (int32_t a = 0; a <= b; ++a) {
        int32_t sum_time = 0;
        for (int32_t i = a; i <= b; ++i) {
            sum_time += tasks[i].pj;
        }
        if (completion_b == tasks[a].rj + sum_time) {
            return a;
        }
    }
    return b;
}
int32_t CarlierSolver::find_c(const std::vector<Task>& tasks, int32_t a,
                              int32_t b) {
    for (int32_t i = b - 1; i >= a; --i) {
        if (tasks[i].dj > tasks[b].dj) {
            return i; // zwróć indeks zadania c
        }
    }
    return -1;
}
void CarlierSolver::modify_tasks(std::vector<Task>& tasks,
                                 const Permutation& new_tasks) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        int idx = new_tasks[i].idx;
        tasks[idx].rj = new_tasks[i].start_time;
        tasks[idx].pj = new_tasks[i].processing_time;
    }
}

void CarlierSolver::carlier_recursive(std::vector<Task>& tasks) {

    Solution schrage_solution = SchrageSolver().solve(tasks);
    int32_t U = schrage_solution.max_lateness;
#ifndef NDEBUG
    std::cout << "Schrage U: " << U << ", Best Lmax: " << best_Lmax 
              << std::endl;
#endif
    if (U < this->best_Lmax) {
        this->best_Lmax = U;
        this->best_solution = schrage_solution;
#ifndef NDEBUG
        std::cout << "New best solution, Lmax: " << best_Lmax << ", "
                  << this->best_solution.sequence << std::endl;
#endif
    }
    Solution preempt_solution = PreemptSchrageSolver().solve(tasks);
    int lower_bound = preempt_solution.max_lateness;
    if (lower_bound >= this->best_Lmax) {
        return;
    }
    std::vector<Task> ordered_tasks;
    for (const auto& item : schrage_solution.sequence) {
        ordered_tasks.push_back(tasks[item.idx]);
    }

    int32_t b = find_b(ordered_tasks);
    // if b is -1, it means that all ordered_tasks are scheduled optimally,
    // and there is no diff between the pmnt and non-pmnt solution
    if (b == -1) {
        return;
    }
    int32_t a = find_a(ordered_tasks, b);
    int32_t c = find_c(ordered_tasks, a, b);
    // optimal solution is found
    if (c == -1) {
        return;
    }
#ifndef NDEBUG
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
#endif
    // identify set (c+1, b)
    int32_t r_K = std::numeric_limits<int32_t>::max();
    int32_t p_K = 0;
    int32_t d_K = std::numeric_limits<int32_t>::max();
    for (int32_t k = c + 1; k <= b; ++k) {
        r_K = std::min(r_K, ordered_tasks[k].rj);
        p_K += ordered_tasks[k].pj;
        d_K = std::max(d_K, ordered_tasks[k].dj);
    }
    // c after new set
    int32_t old_rc = ordered_tasks[c].rj;
    ordered_tasks[c].rj = std::max(ordered_tasks[c].rj, r_K + p_K);
    if (ordered_tasks[c].rj!=old_rc)
        carlier_recursive(ordered_tasks);
    ordered_tasks[c].rj = old_rc;

    // c before new set
    int32_t old_dc = ordered_tasks[c].dj;
    ordered_tasks[c].dj = std::min(ordered_tasks[c].dj, d_K - p_K);
    if (ordered_tasks[c].dj != old_dc)
        carlier_recursive(ordered_tasks);
    ordered_tasks[c].dj = old_dc;
}
Solution CarlierSolver::solve(const Problem& problem) {
    best_solution = Solution(0);
    best_Lmax = std::numeric_limits<int32_t>::max();

    const auto& tasks = problem.getTasks();
    std::vector<Task> tasks_copy = tasks;
    carlier_recursive(tasks_copy);

    return best_solution;
}
