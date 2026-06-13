#include "JohnsonFor2M.hpp"
#include <algorithm>

Solution JohnsonFor2M::solve(const Problem& problem)
{
    const auto &tasks = problem.getTasks();
    int n = tasks.size();
    int m = problem.get_num_machines();

    if (m != 2)
    {
        return Solution(n); //Johnson's algorithm only for 2 machines
    }

    std::vector<Task> tasksL; //tasks with processing time on machine 1 shorter than on machine 2
    std::vector<Task> tasksR; //tasks with processing time on machine 1 longer or equal to on machine 2

    for (const auto& task : tasks)
    {
        if (task.processing_times[0] < task.processing_times[1])
        {
            tasksL.push_back(task);
        }
        else
        {
            tasksR.push_back(task);
        }
    }

    std::stable_sort(tasksL.begin(), tasksL.end(), [](const Task &a, const Task &b)
    {
        return a.processing_times[0] < b.processing_times[0];
    });

    std::stable_sort(tasksR.begin(), tasksR.end(), [](const Task &a, const Task &b)
    {
        return a.processing_times[1] > b.processing_times[1];
    });

    std::vector<Task> tasksJoined;

    tasksJoined.reserve(n);
    tasksJoined.insert(tasksJoined.end(), tasksL.begin(), tasksL.end());
    tasksJoined.insert(tasksJoined.end(), tasksR.begin(), tasksR.end());

    std::vector<int> final_sequence;
    final_sequence.reserve(n);

    for (const auto& task : tasksJoined)
    {
        final_sequence.push_back(task.idx);
    }

    Solution sol(final_sequence);
    sol.evaluate(problem);

    return sol;
}
