#ifndef TASK_HPP_
#define TASK_HPP_

// task of the 1|rj|Lmax problem
struct Task {
    int rj; // termin dostępności
    int pj; // czas przetwarzania
    int dj; // pożądany termin zakończenia (deadline)
    Task(int rj, int pj, int dj) : rj(rj), pj(pj), dj(dj) {
    }
    // we will sort tasks by qj OR by rj
    // nie implementujemy operator<, bo sortujemy po różnych polach
};

#endif /* TASK_HPP_ */
