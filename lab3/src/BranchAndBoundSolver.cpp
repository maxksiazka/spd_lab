#include "BranchAndBoundSolver.hpp"
#include <algorithm>

void BranchAndBoundSolver::LookThroughForN(
    int current_task, int n, int m,
    const std::vector<Task>& tasks, 
    VectorI& current_loads, 
    VectorI& current_assignment, 
    int& best_makespan,
    VectorI& best_assignment)
{
    if (current_task == n)
    {
        int current_max = *std::max_element(current_loads.begin(), current_loads.end());
    
        if (current_max < best_makespan)
        {
            best_makespan = current_max;
            best_assignment = current_assignment;
        }

        return;
    }

    for (int j = 0; j < m; ++j)
    {
        current_loads[j] += tasks[current_task].processing_time;
        current_assignment[current_task] = j;

        if (current_loads[j] < best_makespan)
        {
            LookThroughForN(current_task + 1, n, m, tasks, current_loads,
                           current_assignment, best_makespan, best_assignment);
        }
        current_loads[j] -= tasks[current_task].processing_time;
    }
}

Solution BranchAndBoundSolver::solve(const Problem& problem)
{
    const int n = problem.getTasks().size();
    const int m = problem.get_num_machines();

    const std::vector<Task>& tasks = problem.getTasks();
    std::vector<Task> tasks_copy = tasks;
    Solution solution(n);

    std::stable_sort(tasks_copy.begin(), tasks_copy.end(), [](const Task& a, const Task& b)
    {
        return a.processing_time > b.processing_time;
    });

    VectorI best_assignment(n, 0);
    VectorI current_loads(m, 0);
    VectorI current_assignment(n, 0);

    VectorI lpt_loads(m, 0);
    for (int i = 0; i < n; ++i)
    {
        int min_machine = 0;
        for (int j = 1; j < m; ++j)
        {
            if (lpt_loads[j] < lpt_loads[min_machine]) {
                min_machine = j;
            }
        }
        best_assignment[i] = min_machine;
        lpt_loads[min_machine] += tasks_copy[i].processing_time;
    }

    int best_makespan = *std::max_element(lpt_loads.begin(), lpt_loads.end());

    LookThroughForN(0, n, m, tasks_copy, current_loads, current_assignment, best_makespan, best_assignment);

    for (int i = 0; i < n; ++i)
    {
#ifndef NDEBUG
            std::cout << "Assigning task "<< task.idx << " (time: " << task.processing_time << ") to machine " << min_machine
                  << " (current load: " << machine_loads[min_machine] << ")" << std::endl;
#endif
        const Task& task = tasks_copy[i];
        solution.sequence[task.idx] = best_assignment[i];
    }

    solution.evaluate(problem);

    return solution;
}
