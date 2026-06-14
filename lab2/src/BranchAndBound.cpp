#include "BranchAndBound.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <limits>
#include "NEHSolver.hpp"

Solution BranchAndBound::solve(const Problem& problem)
{
    auto tasks = problem.getTasks();
    int n = tasks.size();
    int m = problem.get_num_machines();

    if (n == 0) return Solution(0);

    NEHSolver neh;
    Solution neh_solution=neh.solve(problem);

    int best_cmax = neh_solution.makespan;
    std::vector<int> best_pi;
    best_pi.reserve(n);

    for (const auto& task_in_seq : neh_solution.sequence)
    {
        best_pi.push_back(task_in_seq.idx);
    }

    int max_id = 0;
    for (const auto& task : tasks)
    {
        if (task.idx > max_id) max_id = task.idx;
    }

    std::vector<Task> safe_tasks(max_id + 1);
    for (const auto& task : tasks)
    {
        safe_tasks[task.idx] = task;
    }

    std::vector<int> current_pi;
    current_pi.reserve(n);

    std::vector<int> remaining_tasks;
    remaining_tasks.reserve(n);

    std::vector<std::vector<int>> tails(n, std::vector<int>(m, 0));
    std::vector<int> sum_remaining(m, 0);
    for (const auto& task : tasks)
    {
        for (int k = 0; k < m; ++k)
        {
            sum_remaining[k] += task.processing_times[k];
            int tail = 0;
            for (int l = k + 1; l < m; ++l)
            {
                tail += task.processing_times[l];
            }
            tails[task.idx][k] = tail;
        }
        remaining_tasks.push_back(task.idx);
    }

    std::vector<int> current_end_times(m, 0);

    //solve_bb(current_pi, remaining_tasks, current_end_times, best_cmax, best_pi, problem);
    solve_bb_fast(current_pi, remaining_tasks, current_end_times, best_cmax, best_pi, sum_remaining, tails, safe_tasks, m);

    Solution sol(best_pi);
    sol.evaluate(problem);

    return sol;
}

void BranchAndBound::solve_bb(
    std::vector<int>& current_pi,
    std::vector<int>& remaining_tasks,
    std::vector<int>& current_end_times,
    int& best_cmax,
    std::vector<int>& best_pi,
    const Problem& problem)
{
    if (remaining_tasks.empty())
    {
        int current_cmax = current_end_times.back();
        if (current_cmax < best_cmax)
        {
            best_cmax = current_cmax;
            best_pi = current_pi;
        }
        return;
    }

    int m = problem.get_num_machines();
    const auto& all_tasks = problem.getTasks();

    for (size_t i = 0; i < remaining_tasks.size(); ++i)
    {
        int next_task_idx = remaining_tasks[i];
        const Task& next_task = all_tasks[next_task_idx];

        std::vector<int> next_end_times(m, 0);
        int prev_machine_end = 0;

        for (int k = 0; k < m; ++k)
        {
            int start_time = std::max(current_end_times[k], prev_machine_end);
            next_end_times[k] = start_time + next_task.processing_times[k];
            prev_machine_end = next_end_times[k];
        }

        std::swap(remaining_tasks[i], remaining_tasks.back());
        remaining_tasks.pop_back();

        int lb = calculate_lower_bound(next_end_times, remaining_tasks, problem);

        if (lb < best_cmax)
        {
            current_pi.push_back(next_task_idx);
            solve_bb(current_pi, remaining_tasks, next_end_times, best_cmax, best_pi, problem);
            current_pi.pop_back();
        }

        remaining_tasks.push_back(next_task_idx);
        std::swap(remaining_tasks[i], remaining_tasks.back());
    }
}

int BranchAndBound::calculate_lower_bound(const std::vector<int>& current_end_times, const std::vector<int>& remaining_tasks, const Problem& problem)
{
    int m = problem.get_num_machines();
    int max_lb = 0;

    const auto& all_tasks = problem.getTasks();

    if (remaining_tasks.empty())
    {
        return current_end_times[m - 1];
    }

    for (int k = 0; k < m; ++k)
    {
        int lb_k = current_end_times[k];
        int sum_remaining_k = 0;
        int min_tail = std::numeric_limits<int>::max();

        for (int task_idx : remaining_tasks)
        {
            const Task &task = all_tasks[task_idx];
            sum_remaining_k += task.processing_times[k];

            int tail = 0;
            for (int l = k + 1; l < m; ++l)
            {
                tail += task.processing_times[l];
            }
            if (tail < min_tail)
            {
                min_tail = tail;
            }
        }

        lb_k += sum_remaining_k + min_tail;

        if (lb_k > max_lb)
        {
            max_lb = lb_k;
        }
    }

    return max_lb;
}

struct BranchNode
{
    int task_idx;
    int remaining_idx;
    int lb;
    std::vector<int> next_end_times;
};

void BranchAndBound::solve_bb_fast(
    std::vector<int>& current_pi,
    std::vector<int>& remaining_tasks,
    const std::vector<int>& current_end_times,
    int& best_cmax,
    std::vector<int>& best_pi,
    std::vector<int>& sum_remaining,
    const std::vector<std::vector<int>>& tails,
    const std::vector<Task>& safe_tasks,
    int m)
{
    if (remaining_tasks.empty())
        {
        int current_cmax = current_end_times.back();
        if (current_cmax < best_cmax)
        {
            best_cmax = current_cmax;
            best_pi = current_pi;
        }
        return;
    }

    std::vector<BranchNode> branches;
    branches.reserve(remaining_tasks.size());

    for (size_t i = 0; i < remaining_tasks.size(); ++i)
    {
        int next_task_idx = remaining_tasks[i];
        const Task& next_task = safe_tasks[next_task_idx];

        std::vector<int> next_end_times(m, 0);
        int prev_machine_end = 0;

        for (int k = 0; k < m; ++k)
        {
            int start_time = std::max(current_end_times[k], prev_machine_end);
            next_end_times[k] = start_time + next_task.processing_times[k];
            prev_machine_end = next_end_times[k];
        }

        int max_lb = 0;
        for (int k = 0; k < m; ++k)
        {
            int current_sum_rem = sum_remaining[k] - next_task.processing_times[k];

            int min_tail = std::numeric_limits<int>::max();
            bool has_others = false;

            for (size_t j = 0; j < remaining_tasks.size(); ++j)
            {
                if (i != j)
                {
                    has_others = true;
                    if (tails[remaining_tasks[j]][k] < min_tail)
                    {
                        min_tail = tails[remaining_tasks[j]][k];
                    }
                }
            }
            if (!has_others) min_tail = 0;

            long long safe_lb = static_cast<long long>(next_end_times[k]) + current_sum_rem + min_tail;
            if (safe_lb > max_lb) max_lb = static_cast<int>(safe_lb);
        }

        if (max_lb < best_cmax)
        {
            branches.push_back({next_task_idx, static_cast<int>(i), max_lb, std::move(next_end_times)});
        }
    }

    std::sort(branches.begin(), branches.end(), [](const BranchNode& a, const BranchNode& b)
    {
        return a.lb < b.lb;
    });

    for (const auto& branch : branches)
    {
        if (branch.lb >= best_cmax) continue;

        int task_idx = branch.task_idx;

        current_pi.push_back(task_idx);
        for(int k=0; k<m; ++k) sum_remaining[k] -= safe_tasks[task_idx].processing_times[k];

        auto it = std::find(remaining_tasks.begin(), remaining_tasks.end(), task_idx);
        int pos = std::distance(remaining_tasks.begin(), it);
        std::swap(remaining_tasks[pos], remaining_tasks.back());
        remaining_tasks.pop_back();

        solve_bb_fast(current_pi, remaining_tasks, branch.next_end_times, best_cmax, best_pi, sum_remaining, tails, safe_tasks, m);

        remaining_tasks.push_back(task_idx);
        std::swap(remaining_tasks[pos], remaining_tasks.back());
        for(int k=0; k<m; ++k) sum_remaining[k] += safe_tasks[task_idx].processing_times[k];
        current_pi.pop_back();
    }
}