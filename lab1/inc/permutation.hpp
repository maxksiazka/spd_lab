#ifndef PERMUTATION_HPP_
#define PERMUTATION_HPP_
// permutation of the 1|rj|Lmax problem

#include <algorithm>
#include <iostream>
#include <vector>

struct subtask {
    int idx;
    int start_time;
    int processing_time;
    subtask() =default;
    subtask(int idx, int start_time, int processing_time)
        : idx(idx), start_time(start_time), processing_time(processing_time) {
    }
    subtask(std::initializer_list<int> list) {
        auto it = list.begin();
        idx = *it++;
        start_time = *it++;
        processing_time = *it;
    }
};
class Permutation {
    std::vector<subtask> sequence;

  public:
    Permutation() = default;
    Permutation(int n) {
        sequence.resize(n);
        for (int i = 0; i < n; ++i) {
            sequence[i].idx = i;
        }
    }
    size_t size() const {
        return sequence.size();
    }
    subtask& operator[](int index) {
        return sequence[index];
    }
    void operator=(const Permutation& other) {
        sequence = other.sequence;
    }
    friend std::ostream& operator<<(std::ostream& os, const Permutation& perm) {
        os << "[";
        for (int i = 0; i < perm.sequence.size(); ++i) {
            os << "(" << perm.sequence[i].idx << ", "
               << perm.sequence[i].start_time << ", "
               << perm.sequence[i].processing_time << ")";
        }
        os << "]" << std::endl;
        return os;
    }
    auto begin() {
        return sequence.begin();
    }
    auto begin() const {
        return sequence.begin();
    }
    auto end() {
        return sequence.end();
    }
    auto end() const {
        return sequence.end();
    }
    auto push_back(const subtask& st) {
        return sequence.push_back(st);
    }
    bool next_permutation() {
        return std::next_permutation(
            sequence.begin(), sequence.end(),
            [](const subtask& a, const subtask& b) { return a.idx < b.idx; });
    }
};

#endif /* PERMUTATION_HPP_ */
