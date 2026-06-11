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
    infile >> num_tasks>> num_machines;
    this->tasks.clear();
    for (int i = 0; i < num_tasks; ++i) {
        std::vector<int> processing_times(num_machines);
        int machine_id;
        for (int j = 0; j < num_machines; ++j) {
            infile >>machine_id >>processing_times[j];
        }
        tasks.emplace_back(i, processing_times);
    }
    // verify that tasks are loaded correctly
    if (infile.fail()) {
        throw std::runtime_error("Error reading tasks from file: " + filename);
    }
#ifndef NDEBUG
    // Print loaded tasks for debugging
    std::cout << "Loaded " << num_tasks << " tasks with " << num_machines << " machines:\n";
    for (const auto& task : tasks) {
        std::cout << "Task " << task.idx << ": ";
        for (size_t j = 0; j < task.processing_times.size(); ++j) {
            std::cout << "Machine " << j << ": " << task.processing_times[j] << " ";
        }
        std::cout << "\n";
    }
#endif
}
