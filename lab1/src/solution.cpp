#include "solution.hpp"
#include <algorithm>

int32_t Solution::evaluate(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    int current_time = 0;

    for (std::size_t i = 0; i < sequence.size(); ++i) {
        const int job_index = sequence[i];
        const Task& task = tasks[job_index];

        current_time =
            std::max(current_time, task.rj) + task.pj; // add processing time

        int lateness =
            current_time - task.dj; // obliczamy nieterminowość (lateness)
        /* std::cout << "Job " << job_index
                  << ": completion time = " << current_time
                  << ", lateness = " << lateness << std::endl; */
        if (lateness > max_lateness) {
            max_lateness = lateness; // aktualizuj Lmax, jeśli jest większa
        }
    }
    return max_lateness;
}
