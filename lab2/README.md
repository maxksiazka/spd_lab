# SPD_LAB2

## Problem FP||Cmax
### Opis implementacji
W tej implementacji rozwiązujemy problem szeregowania zadań na wielu maszynach, gdzie każde zadanie ma określony czas przetwarzania i termin, a celem jest zminimalizowanie czasu wykonywania wszystkich zadań (Cmax).
Kolejność wykonywania zadań jest reprezentowana przez permutację, która określa, w jakiej kolejności zadania będą przetwarzane.

Klasa `Task` reprezentuje pojedyncze zadanie, zawierając informacje o czasach przetwarzania dla każdej maszyny.
Klasa `Permutacja` jest wrapperem na strukturę danych, która zawiera czas przetwarzania i czasy startu dla każdej maszyny.
Klasa `Problem` zawiera wektor zadań oraz funkcję do ładowania danych z pliku.
Klasa `Solution` reprezentuje rozwiązanie problemu, zawierając permutację zadań oraz obliczaną dla danej permutacji wartość funkcji celu (Cmax).
Klasa `Solver` jest klasą bazową dla różnych algorytmów rozwiązujących problem, a konkretne algorytmy dziedziczą po niej i implementują metodę `solve`.


### Jak implementować algorytmy

1. Zdefiniuj klasę, która dziedziczy po `Solver` i implementuje metody:
    - `Solution solve(const Problem& problem) override;`
    - `std::string name() const override;`
2. W metodzie `solve` zaimplementuj logikę algorytmu, korzystając z danych zawartych w obiekcie `problem`.
    - Zwróć obiekt `Solution`, który zawiera przede wszystkim obiekt Permutacja - który jest wrapperem na wektor intów, reprezentujący kolejność wykonywania zadań.
    - Przed zwróceniem tego obiektu, wywołaj funkcję `evaluate`, która obliczy wartość funkcji celu dla danej permutacji.
