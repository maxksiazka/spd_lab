import os
import random

def generate_pm_cmax_benchmark(n_jobs, n_machines, instance_no, min_p=10, max_p=100, folder="benchmarks2M2"):
    """
    Generates a single Pm||Cmax benchmark instance.
    """
    os.makedirs(folder, exist_ok=True)
    filename = f"pm_{n_jobs}_{n_machines}_inst_{instance_no:02d}.txt"
    filepath = os.path.join(folder, filename)

    processing_times = [random.randint(min_p, max_p) for _ in range(n_jobs)]

    with open(filepath, 'w') as f:
        f.write(f"{n_jobs} {n_machines}\n")
        for p in processing_times:
            f.write(f"{p}\n")
    with open(os.path.join(folder, "README.txt"),'a') as f:
        f.write(f"{filename}: {n_jobs} jobs, theoretical lower bound ~{sum(processing_times)//n_machines}\n")
    print(f"Generated: {filepath} (Theoretical Lower Bound: ~{sum(processing_times)//n_machines})")

if __name__ == "__main__":
    random.seed(42) 
    test_configs = {
        2:  [10, 20, 50, 100, 200, 500, 1000],
        # 5:  [20, 50, 100, 200, 500, 1000],
        # 10: [50, 100, 200],
        # 20: [100, 500, 1000]
    }
    print("Generating Pm||Cmax benchmark suite...")
    for m, n_list in test_configs.items():
        for n in n_list:
            for inst in range(1, 2):
                generate_pm_cmax_benchmark(n_jobs=n, n_machines=m, instance_no=inst)
    print("\nDone! Benchmarks saved to the specified directory.")
