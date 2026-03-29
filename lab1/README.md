# SPD_LAB1

## Problem 1|rj|Lmax
### Opis implementacji
W tej implementacji rozwiązujemy problem szeregowania zadań na pojedynczej maszynie, gdzie celem jest minimalizacja maksymalnego opóźnienia (Lmax).

Klasa `Task` reprezentuje pojedyncze zadanie, zawierając informacje o czasie przetwarzania i terminie.
Klasa `Permutacja` jest prostym wrapperem na wektor intów, który reprezentuje kolejność wykonywania zadań.
Klasa `Problem` zawiera wektor zadań oraz funkcję do ładowania danych z pliku.
Klasa `Solution` reprezentuje rozwiązanie problemu, zawierając permutację zadań oraz obliczaną dla danej permutacji wartość funkcji celu (Lmax).
Klasa `Solver` jest klasą bazową dla różnych algorytmów rozwiązujących problem, a konkretne algorytmy dziedziczą po niej i implementują metodę `solve`.


### Jak implementować algorytmy

1. Zdefiniuj klasę, która dziedziczy po `Solver` i implementuje metody:
    - `Solution solve(const Problem& problem) override;`
    - `std::string name() const override;`
2. W metodzie `solve` zaimplementuj logikę algorytmu, korzystając z danych zawartych w obiekcie `problem`.
    - Zwróć obiekt `Solution`, który zawiera przede wszystkim obiekt Permutacja - który jest wrapperem na wektor intów, reprezentujący kolejność wykonywania zadań.
    - Przed zwróceniem tego obiektu, wywołaj funkcję `evaluate`, która obliczy wartość funkcji celu dla danej permutacji.

Polecam popatrzeć na EDDsolver.cpp, który implementuje algorytm EDD (Earliest Due Date) jako przykład implementacji algorytmu rozwiązującego problem.
