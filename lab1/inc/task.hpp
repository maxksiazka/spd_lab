#ifndef TASK_HPP_
#define TASK_HPP_

// task of the 1|rj|Lmax problem
#include <ostream>
struct Task {
    int idx; // task id
    int rj;  // release time
    int pj;  // processing time
    int qj;  // delivery time
    Task(int idx, int rj, int pj, int qj) : idx(idx), rj(rj), pj(pj), qj(qj) {
    }
    friend std::ostream& operator<<(std::ostream& os, const Task& task) {
        os << "Task(idx=" << task.idx << ", rj=" << task.rj
           << ", pj=" << task.pj << ", qj=" << task.qj << ")";
        return os;
    }
};

#endif /* TASK_HPP_ */
