#include "solution.hpp"
#include <algorithm>

int32_t Solution::evaluate(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    int current_time = 0;

    for (std::size_t i = 0; i < sequence.size(); ++i) {
        const subtask job = sequence[i];
        const Task& task = tasks[job.idx];
        

        current_time =
            std::max(current_time, job.start_time) + job.processing_time;

        // patrzymy czy dany index istnieje dalej, eg czy zadanie się
        // zakończyło, czy jest przerwane, czy jest przerwane i potem dokończone
        if (std::find_if(sequence.begin() + i + 1, sequence.end(),
                         [&job](const subtask& s) {
                             return s.idx == job.idx;
                         }) != sequence.end()) {
            continue; // jeśli zadanie jest przerwane, pomijamy obliczanie
                      // lateness
        }
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
