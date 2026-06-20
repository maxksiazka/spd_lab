#ifndef PROBLEM_HPP_
#define PROBLEM_HPP_
#include "task.hpp"
#include <string>
#include <vector>
class Problem {
    int num_machines; // number of machines
    std::vector<Task> tasks; // list of tasks
  public:
    /**
     * @brief a function to load tasks from a file.
     *
     * @param[in] filename -- the name of the file to load tasks from
     */
    void load_tasks_from_file(const std::string& filename);
    const std::vector<Task>& getTasks() const {
        return tasks;
    }
    int get_num_machines() const {
        return num_machines;
    }
    void set_num_machines(int num) {
        num_machines = num;
    }
    Task& operator[](std::size_t index) {
        return tasks[index];
    }
    Problem() = default;
    Problem(int num_machines,const std::vector<Task>& tasks) :num_machines(num_machines), tasks(tasks) {
    }
};

#endif /* PROBLEM_HPP_ */
