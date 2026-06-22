#include "PTASSolver.hpp"
#include <algorithm>

void PTASSolver::LookThroughForK(
    int current_task, int k, int m, 
    const std::vector<Task>& tasks, 
    VectorI& current_loads, 
    VectorI& current_assignment, 
    int& best_makespan,
    VectorI& best_assignment)
{
    if (current_task == k)
    {
        int current_max = *std::max_element(current_loads.begin(), current_loads.end());
    
        if (current_max < best_makespan)
        {
            best_makespan = current_max;
            best_assignment = current_assignment;
        }

        return;
    }

    bool empty_machine_used=false;

    for (int j = 0; j < m; ++j)
    {
        if (current_loads[j] == 0)
        {
            if (empty_machine_used) continue;
            empty_machine_used = true;
        }

        current_loads[j] += tasks[current_task].processing_time;
        current_assignment[current_task] = j;

        if (current_loads[j] < best_makespan)
        {
            LookThroughForK(current_task + 1, k, m, tasks, current_loads,
                           current_assignment, best_makespan, best_assignment);
        }
        current_loads[j] -= tasks[current_task].processing_time;
    }
}

Solution PTASSolver::solve(const Problem& problem)
{

    const int n = problem.getTasks().size();
    const int m = problem.get_num_machines();

    const int k=2;

    const std::vector<Task>& tasks = problem.getTasks();
    std::vector<Task> tasks_copy = tasks;
    Solution solution(n);
    VectorI machine_loads(m, 0);

    const int k_norm = std::min(k, n);

    std::stable_sort(tasks_copy.begin(), tasks_copy.end(), [](const Task& a, const Task& b)
    {
        return a.processing_time > b.processing_time;
    });

    VectorI best_assignment(k_norm, 0);
    int best_makespan = std::numeric_limits<int>::max();
    VectorI current_loads(m, 0);
    VectorI current_assignment(k_norm);

    LookThroughForK(0, k_norm, m, tasks_copy, current_loads, current_assignment, best_makespan, best_assignment);

    for (int i = 0; i < n; ++i)
    {
        if (i<k_norm)
        {
            const Task& task = tasks_copy[i];
            int assigned_machine = best_assignment[i];
            solution.sequence[task.idx] = assigned_machine;
            machine_loads[assigned_machine] += task.processing_time;
        }

        else if (i>=k_norm)
        {
            const Task& task = tasks_copy[i];
            int min_machine = 0;
            for (int j = 1; j < m; ++j)
            {
                if (machine_loads[j] < machine_loads[min_machine])
                {
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
    }

    solution.evaluate(problem);

    return solution;
}
