#include "FNEHSolver.hpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

#ifndef NDEBUG
#include <iostream>
#endif

typedef std::vector<int> VectorI;
typedef std::vector<VectorI> Matrix2I;

struct Job {
    int idx = -1;
    int total_processing_time = 0;
    Job() = default;
    Job(int idx, int total_processing_time)
        : idx(idx), total_processing_time(total_processing_time) {
    }
};

Solution FNEHSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    const int n = tasks.size();
    const int m = problem.get_num_machines();
    std::vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        jobs[i].idx = i;
        for (int j = 0; j < m; ++j) {
            jobs[i].total_processing_time += tasks[i].processing_times[j];
        }
    }
    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        if (a.total_processing_time != b.total_processing_time) {
            return a.total_processing_time > b.total_processing_time;
        }
        return a.idx < b.idx;
    });
    VectorI best_sequence;
    best_sequence.reserve(n);

    for (int i = 0; i < n; ++i) {
        const int K = i;

        // E(i,j) calculation
        Matrix2I e(K, VectorI(m, 0));
        for (int r = 0; r < K; ++r) {
            const int job_idx = best_sequence[r];
            for (int j = 0; j < m; ++j) {
                int val1 = 0, val2 = 0;
                if (r > 0)
                    val1 = e[r - 1][j];
                if (j > 0)
                    val2 = e[r][j - 1];
                e[r][j] =
                    std::max(val1, val2) + tasks[job_idx].processing_times[j];
            }
        }
        // Q(i,j) calculation
        Matrix2I q(K, VectorI(m, 0));
        for (int r = K - 1; r >= 0; --r) {
            const int job_idx = best_sequence[r];
            for (int j = m - 1; j >= 0; --j) {
                int val1 = 0, val2 = 0;
                if (r < K - 1)
                    val1 = q[r + 1][j];
                if (j < m - 1)
                    val2 = q[r][j + 1];
                q[r][j] =
                    std::max(val1, val2) + tasks[job_idx].processing_times[j];
            }
        }

        const int target_job = jobs[i].idx;
        int best_index = -1;
        int best_makespan = std::numeric_limits<int>::max();

#ifndef NDEBUG
        std::cout << "Inserting job " << jobs[i].idx
                  << " with total processing time "
                  << jobs[i].total_processing_time << std::endl;
#endif

        // 3. Find the best insertion position using Taillard's speedup
        VectorI f(m, 0);
        for (int current_index = 0; current_index <= K; ++current_index) {
            // Compute earliest completion times f[j] for the newly inserted job
            for (int j = 0; j < m; ++j) {
                int val1 = 0, val2 = 0;
                if (current_index > 0)
                    val1 = e[current_index - 1][j];
                if (j > 0)
                    val2 = f[j - 1];
                f[j] = std::max(val1, val2) +
                       tasks[target_job].processing_times[j];
            }

            // Calculate total makespan for this trial insertion location
            int current_makespan = 0;
            for (int j = 0; j < m; ++j) {
                int tail = 0;
                if (current_index < K) {
                    tail = q[current_index][j];
                }
                current_makespan = std::max(current_makespan, f[j] + tail);
            }

#ifndef NDEBUG
            VectorI debug_sequence = best_sequence;
            debug_sequence.insert(debug_sequence.begin() + current_index,
                                  jobs[i].idx);
            Solution current_solution(debug_sequence);
            current_solution.evaluate(problem);
            std::cout << "Current sequence: ";
            for (const auto& st : current_solution.sequence) {
                std::cout << st.idx << " ";
            }
            std::cout << "Makespan: " << current_solution.makespan << std::endl;
            assert(current_makespan == current_solution.makespan);
#endif
            if (current_makespan < best_makespan) {
                best_makespan = current_makespan;
                best_index = current_index;
            }
        }

        best_sequence.insert(best_sequence.begin() + best_index, target_job);
    }

    Solution final_solution(best_sequence);
    final_solution.evaluate(problem);
    return final_solution;
}
