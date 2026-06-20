#include "solution.hpp"
#include <algorithm>
#include <cassert>

int32_t Solution::evaluate(const Problem& problem) {
    int n = sequence.size();
    int m = problem.get_num_machines();
    if (n == 0 || m == 0)
        return 0;
    const std::vector<Task>& tasks = problem.getTasks();

    std::vector<int> C(m, 0);

    for (std::size_t i = 0; i < n; ++i) {
        int machine_id = sequence[i];
        assert(machine_id >= 0 && machine_id < m);
        C[machine_id] += tasks[i].processing_time;
    }

    makespan = *std::max_element(C.begin(), C.end());
    return makespan;
}
