#!/usr/bin/env python3
#pyright: basic
import subprocess
import re
import pandas as pd
from pathlib import Path
import sys
import os

# Configuration
BUILD_DIR = Path("./build")
EXECUTABLE = BUILD_DIR / "lab3"
TASK_DIR = Path("./")
ALGORITHMS = ["LSA", "LPT", "Dynamic"]

TASK_FILES = [
    f"benchmarks2M/pm_{i}_2_inst_{inst:02d}.txt" 
    for i in [10, 20, 50, 100, 200, 500, 1000] 
    for inst in range(1, 21)
]
OUTPUT_CSV = Path("./benchmark_results_cmax_2_machines.csv")

def parse_output(stdout: str):
    """Wyciąga OSTATNIE Cmax (oraz opcjonalnie czas wykonania) ze standardowego wyjścia."""
    cmax_matches = re.findall(r"Makespan \(Cmax\):\s*(\d+)", stdout)
    time_matches = re.findall(r"Elapsed time:\s*([\d.e\-+]+)s", stdout)
    
    if not cmax_matches:
        return None, None
    
    cmax = int(cmax_matches[-1])
    
    elapsed_time_ms = None
    if time_matches:
        elapsed_time_ms = float(time_matches[-1]) * 1000
    
    return cmax, elapsed_time_ms

def run_benchmark():
    """Uruchamia benchmarki i zbiera wyniki."""
    results = []
    
    for idx, task_file in enumerate(TASK_FILES):
        print(f"[{idx + 1}/{len(TASK_FILES)}] Processing {task_file}...")
        row = {"Index": idx, "Task": task_file}
        
        for algo in ALGORITHMS:
            print(f"  Running {algo}...", end=" ", flush=True)
            
            try:
                result = subprocess.run(
                    [str(EXECUTABLE), algo, task_file],
                    capture_output=True,
                    text=True,
                    timeout=300
                )
                
                if result.returncode != 0:
                    print(f"FAILED (exit code {result.returncode})")
                    print(f"stderr: {result.stderr}")
                    sys.exit(1)
                
                cmax, elapsed_time_ms = parse_output(result.stdout)
                
                if cmax is None:
                    print("FAILED (parse error - Makespan not found)")
                    print(f"stdout: {result.stdout}")
                    sys.exit(1)
                
                row[f"{algo}_Cmax"] = cmax
                
                if elapsed_time_ms is not None:
                    row[f"{algo}_time"] = float(elapsed_time_ms)
                    print(f"OK (Cmax={cmax}, {elapsed_time_ms:.4f}ms)")
                else:
                    print(f"OK (Cmax={cmax})")
            
            except subprocess.TimeoutExpired:
                print("TIMEOUT")
                sys.exit(1)
            except Exception as e:
                print(f"ERROR: {e}")
                sys.exit(1)
        
        results.append(row)
    
    return results

def main():
    print("CWD: ", os.getcwd())
    if not EXECUTABLE.exists():
        print(f"Error: {EXECUTABLE} not found. Build the project first.")
        sys.exit(1)
    
    print("Starting benchmark suite...")
    results = run_benchmark()
    
    df = pd.DataFrame(results)
    df.to_csv(OUTPUT_CSV, index=False)
    print(f"\nResults saved to {OUTPUT_CSV}")
    print(df)

if __name__ == "__main__":
    main()