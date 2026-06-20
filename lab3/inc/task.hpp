#ifndef TASK_HPP_
#define TASK_HPP_

// task of the Pm||Cmax proble
struct Task {
    int idx;
    int processing_time;
    Task() = default;
    Task(const int idx, const int processing_time) : idx(idx), processing_time(processing_time) {
    }
};

#endif /* TASK_HPP_ */
