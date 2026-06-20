#include "LPTSolver.hpp"
#include <algorithm>

typedef std::vector<int> VectorI;

Solution LPTSolver::solve(const Problem& problem) {
    const int n = problem.getTasks().size();
    const int m = problem.get_num_machines();
    const std::vector<Task>& tasks = problem.getTasks();
    std::vector<Task> tasks_copy = tasks;
    Solution solution(n);
    VectorI machine_loads(m, 0);

    std::stable_sort(tasks_copy.begin(), tasks_copy.end(), [](const Task& a, const Task& b) {
        return a.processing_time > b.processing_time;
    });

    for (int i = 0; i < n; ++i) {
        const Task& task = tasks_copy[i];
        int min_machine = 0;
        for (int j = 1; j < m; ++j) {
            if (machine_loads[j] < machine_loads[min_machine]) {
                min_machine = j;
            }
        }
#ifndef NDEBUG
        std::cout << "Assigning task "<< task.idx << " (time: " << task.processing_time << ") to machine " << min_machine
                  << " (current load: " << machine_loads[min_machine] << ")" << std::endl;
#endif
        solution.sequence[task.idx] = min_machine;
        machine_loads[min_machine] += task.processing_time;
    }

    solution.evaluate(problem);
    return solution;
}
