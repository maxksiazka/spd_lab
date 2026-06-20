#include "LSASolver.hpp"
#include "LPTSolver.hpp"
#include "solver.hpp"
#include <chrono>
#include <iostream>

typedef enum {
    LSA = 0,
    LPT,
    PD,
    LookThrough,
    PTAS,
    FPTAS
} Algorithm_t;

const char* algorithm_names[] = {"LSA",         "LPT",  "PD",
                                 "LookThrough", "PTAS", "FPTAS"};

void run_benchmark(Solver* solver, const std::string& tasks_file) {
    Problem problem;
    try {
        problem.load_tasks_from_file(tasks_file);
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return;
    }
    if (solver == nullptr) {
        std::cerr << "Solver instance is null" << std::endl;
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
    int num_of_machines = problem.get_num_machines();
    std::vector<std::vector<std::pair<int, int>>> machines(num_of_machines);
    for (size_t i = 0; i < solution.sequence.size(); ++i) {
        int machine_id = solution.sequence[i];
        machines[machine_id].push_back({i, problem[i].processing_time});
    }

    std::cout << "Result sequence: (task_id, processing_time)" << std::endl;

    int machine_index = 0;
    for (const auto& machine_tasks : machines) {

        std::cout << "Machine " << machine_index << ": [";
        for (size_t j = 0; j < machine_tasks.size(); ++j) {
            std::cout << "(" << machine_tasks[j].first << ", "
                      << machine_tasks[j].second << ")";
            if (j < machine_tasks.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "] " << std::endl;
        machine_index++;
    }
    std::cout << "Makespan (Cmax): " << solution.makespan << std::endl;
    std::cout << "===============================" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    Solver* selected_solver = nullptr;
    Algorithm_t algorithm = LSA;
    int num_algorithms = sizeof(algorithm_names) / sizeof(algorithm_names[0]);
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <algorithm> <tasks_file>"
                  << std::endl;
        std::cerr << "Available algorithms:" << std::endl;
        return 1;
    }
    filename = argv[2];
    if (filename.empty()) {
        std::cerr << "Empty tasks file provided" << std::endl;
        return 1;
    }
    std::string alg_str = argv[1];
    if (alg_str.empty()) {
        std::cerr << "Empty algorithm name provided" << std::endl;
        return 1;
    }
    for (int i = 0; i < num_algorithms; ++i) {
        if (alg_str == algorithm_names[i]) {
            algorithm = static_cast<Algorithm_t>(i);
            break;
        }
    }
    switch (algorithm) {
    case LSA:
        selected_solver = new LSASolver();
        break;
        case LPT:
            selected_solver = new LPTSolver();
            break;
        // case PD:
        //     selected_solver = new PDSolver();
        //     break;
        // case LookThrough:
        //     selected_solver = new LookThroughSolver();
        //     break;
        // case PTAS:
        //     selected_solver = new PTASSolver();
        //     break;
        // case FPTAS:
        //     selected_solver = new FPTASSolver();
        //     break;
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
