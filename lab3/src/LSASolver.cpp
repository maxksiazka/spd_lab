#include "LSASolver.hpp"

typedef std::vector<int> VectorI;

Solution LSASolver::solve(const Problem& problem) {
    const int n = problem.getTasks().size();
    const int m = problem.get_num_machines();
    const std::vector<Task>& tasks = problem.getTasks();
    Solution solution(n);
    VectorI machine_loads(m, 0);

    for (int i = 0; i < n; ++i) {
        const Task& task = tasks[i];
        int min_machine = 0;
        for (int j = 1; j < m; ++j) {
            if (machine_loads[j] < machine_loads[min_machine]) {
                min_machine = j;
            }
        }
#ifndef NDEBUG
        std::cout << "Assigning task " << task.idx << " (time: " << task.processing_time << ") to machine " << min_machine
                  << " (current load: " << machine_loads[min_machine] << ")" << std::endl;
#endif
        solution.sequence[i] = min_machine;
        machine_loads[min_machine] += task.processing_time;
    }

    solution.evaluate(problem);
    return solution;
}
