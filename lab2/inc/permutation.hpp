#ifndef PERMUTATION_HPP_
#define PERMUTATION_HPP_
// permutation of the FP||Cmax problem

#include <algorithm>
#include <iostream>
#include <vector>

struct subtask {
    int idx;
    std::vector<int> start_times;
    std::vector<int> processing_times;
    subtask() = default;
    subtask(int idx) : idx(idx) {
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
    Permutation(const std::vector<int>& seq) {
        sequence.resize(seq.size());
        for (size_t i = 0; i < seq.size(); ++i) {
            sequence[i].idx = seq[i];
        }
    }
    size_t size() const {
        return sequence.size();
    }
    const subtask& operator[](int index) const {
        return sequence[index];
    }
    subtask& operator[](int index) {
        return sequence[index];
    }
    void operator=(const Permutation& other) {
        sequence = other.sequence;
    }
    friend std::ostream& operator<<(std::ostream& os, const Permutation& perm) {
        os << "[";
        for (const auto& st : perm.sequence) {
            os << st.idx << " ";
        }
        os << "]";
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
    bool next_permutation() {
        return std::next_permutation(
            sequence.begin(), sequence.end(),
            [](const subtask& a, const subtask& b) { return a.idx < b.idx; });
    }
};

#endif /* PERMUTATION_HPP_ */
