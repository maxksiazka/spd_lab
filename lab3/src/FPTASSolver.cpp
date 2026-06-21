#include "FPTASSolver.hpp"
#include <cmath>
#include <numeric>

typedef std::vector<int> VectorI;
typedef std::vector<std::vector<int>> MatrixI;

// solver for P2||Cmax using FPTAS
Solution FPTASSolver::solve(const Problem& problem)
{
    const std::vector<Task>& tasks = problem.getTasks();
    const int m = problem.get_num_machines();
    const int n = tasks.size();

    Solution solution(n);

    double K = 3;

    VectorI scaled_p(n);
    long long scaled_sum = 0;
    for (int i = 0; i < n; ++i)
    {
        scaled_p[i] = static_cast<int>(std::floor(tasks[i].processing_time / K));
        scaled_sum += scaled_p[i];
    }

    int rows = n + 1;
    int cols = (scaled_sum/2)+1;

    MatrixI T(rows, VectorI(cols, 0));
    // fill first column with 1s
    for (int i = 0; i < rows; ++i) {
        T[i][0] = 1;
    }

    for (int j = 1; j < rows; ++j)
    {
        for (int k = 1; k < cols; ++k)
        {
            int pj = scaled_p[j-1];

            if (T[j - 1][k] == 1)
            {
                T[j][k] = 1;
            } else if (k >= pj)
            {
                if (T[j - 1][k - pj] == 1) 
                {
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
    while (k > 0 && T[rows - 1][k] == 0)
    {
        k--;
    }
    int j = rows - 1;
    for (; j > 0; --j)
    {
        if (T[j][k] == 1 && T[j - 1][k] == 0)
        {
            // task j correlates to j-1 in task list
            k -= scaled_p[j - 1];
            solution.sequence[tasks[j - 1].idx] = 1;
        }
    }
    solution.evaluate(problem);
    return solution;
}
