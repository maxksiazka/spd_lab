#include "NEHSolver.hpp"
#include <cassert>

struct Job {
    int idx = -1;
    int total_processing_time = 0;
    Job() = default;
    Job(int idx, int total_processing_time)
        : idx(idx), total_processing_time(total_processing_time) {
    }
};
Solution NEHSolver::solve(const Problem& problem) {
    const auto& tasks = problem.getTasks();
    int n = tasks.size();
    int m = problem.get_num_machines();
    std::vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        jobs[i].idx = i;
        for (int j = 0; j < m; ++j) {
            jobs[i].total_processing_time += tasks[i].processing_times[j];
        }
    }
    std::for_each(jobs.begin(), jobs.end(), [n](Job& job) {
        assert(job.idx >= 0 && job.total_processing_time >= 0 &&
               job.total_processing_time < std::numeric_limits<int>::max() &&
               job.idx < n);
    });
    // non-decreasing order of total processing time
    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.total_processing_time <= b.total_processing_time;
    });
    std::vector<int> best_sequence;
    best_sequence.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::vector<int> current_sequence = best_sequence;
        int best_index = -1;
        int best_makespan = std::numeric_limits<int>::max();
        // we try to insert the current job at every possible position in the
        // current sequence and keep track of the best makespan and the
        // corresponding index
#ifndef NDEBUG
        std::cout << "Inserting job " << jobs[i].idx
                  << " with total processing time "
                  << jobs[i].total_processing_time << std::endl;
#endif
        for (int current_index = 0; current_index <= i; ++current_index) {
            current_sequence.insert(current_sequence.begin() + current_index, jobs[i].idx);
            // if size 0, then the only place we can insert is at index 0, if
            // size 1, then we can insert at index 0 or 1, if size 2, then we
            // can insert at index 0, 1, or 2, and so on
            Solution current_solution(current_sequence);
            current_solution.evaluate(problem);
#ifndef NDEBUG
            std::cout << "Current sequence: ";
            for (const auto& st : current_solution.sequence) {
                std::cout << st.idx << " ";
            }
            std::cout << "Makespan: " << current_solution.makespan << std::endl;
#endif
            if (current_solution.makespan <= best_makespan) {
                best_makespan = current_solution.makespan;
                best_index = current_index;
            }
            current_sequence.erase(current_sequence.begin() + current_index);
        }
        best_sequence.insert(best_sequence.begin() + best_index, jobs[i].idx);
        assert(best_index >= 0 && best_index <= current_sequence.size());
    }
    Solution final_solution(best_sequence);
    final_solution.evaluate(problem);
    return final_solution;
}
