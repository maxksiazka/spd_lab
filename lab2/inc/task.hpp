#ifndef TASK_HPP_
#define TASK_HPP_

// task of the FP||Cmax problem
#include <vector>
struct Task {
    int idx; // index of the task

    std::vector<int> processing_times; // processing times on each machine
    Task() = default;
    Task(int idx, const std::vector<int>& processing_times) : idx(idx), processing_times(processing_times) {
    }
};

#endif /* TASK_HPP_ */
