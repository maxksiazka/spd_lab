#include "ConstructionSolver.hpp"
#include <algorithm>
// implementacja algorytmu Construction (heurystyka konstrukcyjna sortująca zadania wstępnie według czasu zakończenia)
// potraktuj to jako templatkę do implementacji innych algorytmów.
// wystarczy zmienić kryterium sortowania na inny algorytm np. schrage
std::string ConstructionSolver::name() const {
    return "Construction Heuristic (EDD-based as initial sequence)";
}
Solution ConstructionSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    Solution solution(tasks.size());
    Permutation& perm = solution.sequence;

    for (int i = 0; i < tasks.size(); ++i) {
        perm[i] = {i, tasks[i].rj, tasks[i].pj}; 
    }
    std::stable_sort(perm.begin(), perm.end(),
            [&tasks](const subtask& i, const subtask& j) { return tasks[i.idx].dj < tasks[j.idx].dj; });

    std::vector<subtask> Current_Task_sequence={perm[0]};

    for (int i=1;i<perm.size();++i)
    {
        subtask new_task=perm[i];

        std::vector<subtask> best_sequence;
        int best_Lmax = std::numeric_limits<int>::max();

        for (int j=i;j>=0;--j)
        {
            std::vector<subtask> temp_sequence=Current_Task_sequence;
            temp_sequence.insert(temp_sequence.begin()+j,new_task);
            
            int current_time=0;

            int current_Lmax=std::numeric_limits<int>::min();

            for (const auto& task : temp_sequence)
            {
                if (current_time < task.start_time) {
                    current_time = task.start_time;
                }

                current_time += task.processing_time;

                int L = current_time - tasks[task.idx].dj;
                if (L > current_Lmax)
                {
                    current_Lmax = L;
                }
            }
            
            if (current_Lmax <= best_Lmax)
            {
                best_Lmax = current_Lmax;
                best_sequence = temp_sequence;
            }
        }
        Current_Task_sequence = best_sequence;
    }

    int actual_time = 0;

    for (int i = 0; i < perm.size(); ++i)
    {
        subtask task = Current_Task_sequence[i];

        if(actual_time < tasks[task.idx].rj)
        {
            actual_time = tasks[task.idx].rj;
        }

        perm[i] = {task.idx, actual_time, tasks[task.idx].pj};

        actual_time += tasks[task.idx].pj;
    }

    solution.evaluate(problem);
    return solution;
}
