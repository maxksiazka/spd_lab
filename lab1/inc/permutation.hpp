#ifndef PERMUTATION_HPP_
#define PERMUTATION_HPP_
// permutation of the 1|rj|Lmax problem

#include <algorithm>
#include <iostream>
#include <vector>

class Permutation {
    std::vector<int> sequence;

  public:
    Permutation() = default;
    Permutation(int n) {
        sequence.resize(n);
        for (int i = 0; i < n; ++i) {
            sequence[i] = i;
        }
    }
    size_t size() const {
        return sequence.size();
    }
    int &operator[](int index) {
        return sequence[index];
    }
    int operator==(const Permutation& other) const {
        return sequence == other.sequence;
    }
    void operator=(const Permutation& other) {
        sequence = other.sequence;
    }
    friend std::ostream& operator<<(std::ostream& os, const Permutation& perm) {
        os << "[";
        for (int i = 0; i < perm.sequence.size(); ++i) {
            os << perm.sequence[i] << ", ";
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
        return std::next_permutation(sequence.begin(), sequence.end());
    }
};

#endif /* PERMUTATION_HPP_ */
