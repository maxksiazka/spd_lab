#include "solution.hpp"
#include <algorithm>

int32_t Solution::evaluate(const Problem& problem) {
    int n = sequence.size();
    int m = problem.get_num_machines();
    if (n == 0 || m == 0)
        return 0;

    std::vector<int> C(m, 0);

    for (int i = 0; i < n; ++i) {
        int job_idx = sequence[i].idx;
        const Task& task = problem.getTasks()[job_idx];
        sequence[i].start_times.resize(m);
        sequence[i].processing_times.resize(m);
        sequence[i].processing_times = task.processing_times;

        for (int j = 0; j < m; ++j) {
            int machine_ready_time = C[j];
            int ready_from_previous_stage;
            if (j != 0)
                ready_from_previous_stage = C[j - 1];
            else
                ready_from_previous_stage = 0;

            int start_time =
                std::max(machine_ready_time, ready_from_previous_stage);

            sequence[i].start_times[j] = start_time;
            C[j] = start_time + task.processing_times[j];
        }
    }

    // The makespan is the completion time of the last job on the last machine
    makespan = C[m - 1];
    return makespan;
}
