#include "DynamicSolver.hpp"
#include <cmath>
#include <numeric>
typedef std::vector<std::vector<int>> MatrixI;
typedef std::vector<int> VectorI;

// solver for P2||Cmax using dynamic programming
Solution DynamicSolver::solve(const Problem& problem) {
    const std::vector<Task>& tasks = problem.getTasks();
    Solution solution(tasks.size());
    int m = problem.get_num_machines();

    int rows = tasks.size() + 1;
    int cols = static_cast<int>(
        std::floor(std::accumulate(tasks.begin(), tasks.end(), 0,
                                   [](float sum, const Task& task) {
                                       return sum + task.processing_time;
                                   }) /
                   2) +
        1);
    MatrixI T(rows, VectorI(cols, 0));
    // fill first column with 1s
    for (int i = 0; i < rows; ++i) {
        T[i][0] = 1;
    }

    for (int j = 1; j < rows; ++j) {
        for (int k = 1; k < cols; ++k) {
            // task j correlates to j-1 in task list
            int pj = tasks[j - 1].processing_time;
            if (T[j - 1][k] == 1) {
                T[j][k] = 1;
            } else if (k >= pj) {
                if (T[j - 1][k - pj] == 1) {
                    T[j][k] = 1;
                }
            }
        }
    }
#ifndef NDEBUG
#include <iostream>
    std::cout << "T:\n";
    for (const auto& row : T) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
#endif
    // backtrack
    int k = cols - 1;
    int j = rows - 1;
    for (; j > 0; --j) {
        if (T[j][k] == 1 && T[j - 1][k] == 0) {
            // task j correlates to j-1 in task list
            k -= tasks[j - 1].processing_time;
            solution.sequence[tasks[j - 1].idx] = 1;
        }
    }
    solution.evaluate(problem);
    return solution;
}
