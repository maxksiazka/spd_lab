#include "problem.hpp"

#include <fstream>

void Problem::load_tasks_from_file(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    int num_tasks;
    infile >> num_tasks;
    this->tasks.clear();
    for (int i = 0; i < num_tasks; ++i) {
        int rj, pj, dj;
        infile >> rj >> pj >> dj;
        this->tasks.push_back({rj, pj, dj});
    }
    // verify that tasks are loaded correctly
    if (infile.fail()) {
        throw std::runtime_error("Error reading tasks from file: " + filename);
    }
}
