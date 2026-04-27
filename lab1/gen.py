import random
import os
#pyright:basic

def generate_instance(n, folder, index):
    # Suma czasów wykonywania dla skalowania rj i dj
    # Przyjmujemy pj w zakresie 1-50
    p_total = n * 25 
    
    tasks = []
    for _ in range(n):
        pj = random.randint(1, 50)
        # rj w połowie całkowitego czasu, by zadania na siebie nachodziły
        rj = random.randint(0, int(p_total * 0.5))
        # dj tak, by lateness było prawdopodobne (rj + pj + zapas)
        dj = rj + pj + random.randint(0, int(p_total * 0.5))
        tasks.append((rj, pj, dj))
    
    filename = f"{folder}/task_{index}.txt"
    with open(filename, 'w') as f:
        f.write(f"{n}\n")
        for r, p, d in tasks:
            f.write(f"{r} {p} {d}\n")

# Konfiguracja
task_counts = [5, 7, 9, 12, 50]
instances_per_count = 50
output_dir = "test_data"


for n in task_counts:
    print(f"Generowanie instancji dla n={n}...")

    if not os.path.exists(f"{output_dir}{n}"):
        os.makedirs(f"{output_dir}{n}")
    for i in range(1, instances_per_count + 1):
        generate_instance(n, f"{output_dir}{n}", i)

print(f"Gotowe! Pliki znajdują się w folderze '{output_dir}'")
