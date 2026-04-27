#include "CarlierSolver.hpp"
#include "ConstructionSolver.hpp"
#include "EDDsolver.hpp"
#include "ERDsolver.hpp"
#include "LookThroughSolver.hpp"
#include "PreemptSchrageSolver.hpp"
#include "SchrageSolver.hpp"
#include "solver.hpp"
#include <chrono>
#include <iostream>
typedef enum {
    EDD = 0,
    ERD,
    LookThrough,
    Schrage,
    PreemptSchrage,
    Construction,
    Carlier
} Algorithm_t;
const char* algorithm_names[] = {
    "EDD",          "ERD",    "LookThrough", "Schrage", "PreemptSchrage",
    "Construction", "Carlier"};

void run_benchmark(Solver* solver, const std::string& tasks_file) {
    Problem problem;
    try {
        problem.load_tasks_from_file(tasks_file);
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return;
    }
    std::cout << "===============================" << std::endl;
    std::cout << "Running benchmark for solver: " << solver->name()
              << std::endl;
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    Solution solution = solver->solve(problem);
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;
    std::cout << "Result sequence: " << solution.sequence << std::endl;
    std::cout << "Maximum lateness (Lmax): " << solution.max_lateness
              << std::endl;
    std::cout << "===============================" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    std::size_t num_algorithms =
        sizeof(algorithm_names) / sizeof(algorithm_names[0]);
    Algorithm_t algorithm;
    Solver* selected_solver = nullptr;
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <algorithm> <tasks_file>"
                  << std::endl;
        std::cerr<<"Available algorithms:"<<std::endl;
        for (size_t i =0; i < num_algorithms; ++i) {
            std::cerr << " - " << algorithm_names[i] << std::endl;
        }
        return 1;
    }
    filename = argv[2];
    if (filename.empty()) {
        std::cerr << "Empty tasks file provided"<<std::endl;
        return 1;
    }
    std::string alg_str = argv[1];
    if (alg_str.empty()) {
        std::cerr << "Empty algorithm name provided"<<std::endl;
        return 1;
    }
    for (int i = 0; i < num_algorithms; ++i) {
        if (alg_str == algorithm_names[i]) {
            algorithm = Algorithm_t(i);
            break;
        }
    }
    switch (algorithm) {
    case EDD:
        selected_solver = new EDDSolver();
        break;
    case ERD:
        selected_solver = new ERDSolver();
        break;
    case LookThrough:
        selected_solver = new LookThroughSolver();
        break;
    case Schrage:
        selected_solver = new SchrageSolver();
        break;
    case PreemptSchrage:
        selected_solver = new PreemptSchrageSolver();
        break;
    case Construction:
        selected_solver = new ConstructionSolver();
        break;
    case Carlier:
        selected_solver = new CarlierSolver();
        break;
    default:
        std::cerr << "Unknown algorithm: " << alg_str
                  << ". Available algorithms are:" << std::endl;
        for (int i = 0; i < num_algorithms; ++i) {
            std::cerr << "  - " << algorithm_names[i] << std::endl;
        }
        return 1;
    }
    if (selected_solver == nullptr) {
        throw std::runtime_error("Failed to create solver instance");
    }
    run_benchmark(selected_solver, filename);
    delete selected_solver;

    return 0;
}
