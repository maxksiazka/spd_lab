#include "problem.hpp"

#include <fstream>
#include <iostream>

void Problem::load_tasks_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    int num_tasks;
    int num_machines;
    infile >> num_tasks >> num_machines;
    this->tasks.clear();
    for (int i = 0; i < num_tasks; ++i) {
        int processing_time;
        infile >> processing_time;
        tasks.emplace_back(i, processing_time);
    }
    set_num_machines(num_machines);
    if (infile.fail()) {
        throw std::runtime_error("Error reading tasks from file: " + filename);
    }
#ifndef NDEBUG
    std::cout << "Loaded " << num_tasks << " tasks with " << num_machines
              << " machines:\n";
    for (const auto& task : tasks) {
        std::cout << "Task " << task.idx << ": " << task.processing_time << "\n";
    }
#endif
}
