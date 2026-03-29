#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include "problem.hpp"
#include <vector>
struct Solution{
    std::vector<int> sequence; // sequence of job indices
    int max_completion_time; // maximum completion time (Lmax)
    std::vector<int> completion_times; // completion times for each job

    void evaluate(const Problem& problem) {
        const auto& tasks = problem.getTasks();
        int current_time = 0;
        max_completion_time = 0;
        completion_times.clear();

        for (int job_index : sequence) {
            const Task& task = tasks[job_index];
            current_time += task.processing_time; // assuming no release times
            completion_times.push_back(current_time);
            if (current_time > max_completion_time) {
                max_completion_time = current_time;
            }
        }
    }
};
#endif /* SOLUTION_HPP_ */

