#include "solver.hpp"
#include <iostream>
#include <chrono>
#include "EDDsolver.hpp"
#include "PreemptSchrageSolver.hpp"
#include "LookthroughSolver.hpp"
#include "ERDsolver.hpp"
#include "Schragesolver.hpp"

void run_benchmark(Solver* solver, const std::string& tasks_file) {
    Problem problem;
    try {
        problem.load_tasks_from_file(tasks_file);
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return;
    }
    std::cout<<"==============================="<<std::endl;
    std::cout << "Running benchmark for solver: " << solver->name() << std::endl;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    Solution solution = solver->solve(problem);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Result sequence: " << solution.sequence << std::endl;
    std::cout << "Maximum lateness (Lmax): " << solution.max_lateness
              << std::endl;
    std::cout<<"==============================="<<std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename = "test.txt";
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <tasks_file>" << std::endl;
        std::cerr << "No tasks file provided, using default: " << filename
                  << std::endl;
    }
    else {
        filename = argv[1];
        if (filename.empty()) {
            std::cerr << "Empty tasks file provided, using default: " << filename
                      << std::endl;
            filename = "tasks.txt";
        }

    }
    EDDSolver edd_solver;
    run_benchmark(&edd_solver, filename);
    ERDSolver erd_solver;
    run_benchmark(&erd_solver, filename);
    LookthroughSolver lookthrough_solver;
    run_benchmark(&lookthrough_solver, filename);
    SchrageSolver schrage_solver;
    run_benchmark(&schrage_solver, filename);
    PreemptSchrageSolver schrage2_solver;
    run_benchmark(&schrage2_solver, filename);
    return 0;

}

