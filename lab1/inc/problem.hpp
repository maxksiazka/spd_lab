#ifndef PROBLEM_HPP_
#define PROBLEM_HPP_
#include "task.hpp"
#include <string>
#include <vector>
class Problem {
    std::vector<Task> tasks; // list of tasks
  public:
    /**
     * @brief a function to load tasks from a file. The file format is as
     * follows:
     *
     * The first line contains an integer n, the number of tasks. Each of the
     * next n lines contains three integers rj, pj, qj, representing the release
     * time, processing time, and delivery time of task j, respectively.
     *
     * @param[in] filename -- the name of the file to load tasks from
     */
    void load_tasks_from_file(const std::string& filename);
    const std::vector<Task>& getTasks() const {
        return tasks;
    }
};

#endif /* PROBLEM_HPP_ */
