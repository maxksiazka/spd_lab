#ifndef PERMUTATION_HPP_
#define PERMUTATION_HPP_
// permutation of the FP||Cmax problem
#include <iostream>
#include <vector>

class Permutation {
  private:
      // job_to_machine[i] = j --  means job i is assigned to machine j
    std::vector<int> job_to_machine;

  public:
    Permutation() = default;
    Permutation(int n) {
        job_to_machine.assign(n, 0);
    }
    Permutation(const std::vector<int>& seq) {
        job_to_machine = seq;
    }
    size_t size() const {
        return job_to_machine.size();
    }
    const int& operator[](int index) const {
        return job_to_machine[index];
    }
    int& operator[](int index) {
        return job_to_machine[index];
    }
    void operator=(const Permutation& other) {
        job_to_machine = other.job_to_machine;
    }
    friend std::ostream& operator<<(std::ostream& os, const Permutation& perm) {
        os << "[";
        for (int m : perm.job_to_machine) {
            os << m << " ";
        }
        os << "]";
        return os;
    }
    auto begin() {
        return job_to_machine.begin();
    }
    auto begin() const {
        return job_to_machine.begin();
    }
    auto end() {
        return job_to_machine.end();
    }
    auto end() const {
        return job_to_machine.end();
    }
    bool next_permutation() {}
};

#endif /* PERMUTATION_HPP_ */
